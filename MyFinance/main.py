import pandas as pd
from pathlib import Path
from flask import Flask
from datetime import date
import matplotlib.pyplot as plt
import matplotlib

matplotlib.use('Agg')

# Слова исключения
EXCEPTIONS = ["антон", "между своими счетами", "перевод по номеру телефона в сбербанк", "альфа-банк", "t-банк",
              "mirris", "evo_kanc"]

# Словарь категоризации расходов
EXPENSE_MAP = {
    "Продукты": ["yarche", "pyaterochka", "magnit", "spar", "krasnoe", "продукт", "tushenka", "пятёрочка"],
    "Фастфуд": ["solnechnyj den", "burger king", "rostics", "shaurma", "stepanov", "shmorgunov", "olvik", "slavica",
                "habibi food", "vkusnoitochka", "lepestok", "batuyeva", "molokova", "nechunaev", "agni"],
    "Транспорт": ["tpp_metro", "proezd", "вокзал", "авиакомпания", "метро", "prigorod"],
    "Прачечная": ["pkk"],
    "Здоровье": ["ингосстрах", "fabrika"],
    "Связь": ["t2"],
    "Переводы": ["екатерина", "перевод"],
    "Подписки": ["подписк"],
}

# Словарь категоризации доходов
INCOME_MAP = {
    "Родители": ["михаил", "наталья"],
    "Бабушка": ["валентина"],
    "Стипендия": ["стипендия"],
    "Проценты": ["процент", "кешбек", "cash"],
    "Переводы": ["александр"]
}

# Описание ---> Категория
def category_income(description):
    d = str(description).lower()
    for category, values in INCOME_MAP.items():
        for word in values:
            if word in d:
                return category
    return description

# Описание ---> Категория
def category_expense(description):
    d = str(description).lower()
    for category, values in EXPENSE_MAP.items():
        for word in values:
            if word in d:
                return category
    return "Прочее"

# Парсер Альфа-банка
def parse_alfa(path):
    df = pd.read_csv(path, sep=",")
    df = df[["operationDate", "amount", "type", "merchant"]]
    df["amount"] = pd.to_numeric(df["amount"], errors="coerce")
    df.loc[df["type"] == "Списание", "amount"] = -df["amount"]
    df = df[["operationDate", "amount", "merchant"]]
    df.columns = ["Дата", "Сумма", "Описание"]
    df["Дата"] = pd.to_datetime(df["Дата"])
    return df

# Парсер СберБанка
def parse_sber(path):
    df = pd.read_csv(path, sep=",", header=None, names=["Дата", "Тип", "Описание", "Сумма", "Баланс",
                                                        "Столбец 7", "Категория", "Столбец 9"])
    df = df[["Дата", "Сумма", "Описание"]]
    df["Дата"] = pd.to_datetime(df["Дата"].str[:10])
    return df

# Парсер Т-Банка
def parse_tbank(path):
    df = pd.read_csv(path, sep=";", decimal=",")
    df = df[["Дата операции", "Сумма операции", "Описание"]]
    df.columns = ["Дата", "Сумма", "Описание"]
    df["Дата"] = pd.to_datetime(df["Дата"].str[:10], dayfirst=True)
    return df

# Парсер ВТБ
def parse_vtb(path):
    df = pd.read_excel(path, engine="openpyxl")
    df = df.dropna(how='all')
    df["Описание"] = df["Описание"].fillna("") + df["Другое"].fillna("")
    df["Сумма"] = df["Поступление"].fillna(0) + df["Расход"].fillna(0)
    df = df[["Дата", "Сумма", "Описание"]]
    df["Дата"] = pd.to_datetime(df["Дата"], errors="coerce")
    return df

# Создание диаграммы
def create_diagram(data, filename):
    fig, ax = plt.subplots()

    colors = ['#66BB6A', '#42A5F5', '#FFCA28', '#EF5350', '#AB47BC', '#5C6BC0', '#FF7043', '#8D6E63',
              '#78909C', '#D4E157', '#7E57C2', '#29B6F6']

    def percent_filter(percent):
        return f'{percent:.1f}%' if percent > 5 else ''

    legenda = [f'{category} ({value * 100 / data.values.sum():.1f}%)' for category, value in data.items()]

    ax.pie(data.values, labels=None, autopct=percent_filter, startangle=90, colors=colors[:len(data)],
           explode=[0.03] * len(data), wedgeprops={'edgecolor': 'white', 'linewidth': 1}, pctdistance=0.6,
           textprops = {'fontsize': 8, 'color': 'white', 'fontweight': 'bold'})

    ax.legend(labels=legenda, loc='center right', bbox_to_anchor=(-0.1, 0.5),
              frameon=False, fontsize=10)

    plt.savefig(f'static/{filename}', bbox_inches='tight', dpi=100, transparent=True)
    plt.close()

########################################################################################

data_files = list(Path("data").glob("*.csv")) + list(Path("data").glob("*.xlsx"))

# Проверка на то что есть файлы для парсера
if not data_files:
    print("Папка Data пуста")
    exit(1)

# Выбор парсера для каждого файла
table = None
all_table = []
for filepath in data_files:
    match filepath.name:
        case "Alfa-Bank.csv":
            table = parse_alfa(filepath)
        case "SberBank.csv":
            table = parse_sber(filepath)
        case "TBank.csv":
            table = parse_tbank(filepath)
        case "VTB.xlsx":
            table = parse_vtb(filepath)
    all_table.append(table)


# Объединения всех таблиц
all_df = pd.concat(all_table)
all_df["Сумма"] = pd.to_numeric(all_df["Сумма"], errors="coerce")
all_df = all_df[all_df["Сумма"] != 0]
exceptions_pattern = '|'.join(EXCEPTIONS)
all_df = all_df[~all_df["Описание"].str.lower().str.contains(exceptions_pattern)]

# Таблица доходов
table_income = all_df[all_df["Сумма"] > 0].copy()
table_income["Категория"] = table_income["Описание"].apply(category_income)
table_income = table_income.groupby("Категория")["Сумма"].sum()

# Таблица расходов
table_expense = all_df[all_df["Сумма"] < 0].copy()
table_expense["Категория"] = table_expense["Описание"].apply(category_expense)
table_expense = table_expense.groupby("Категория")["Сумма"].sum()

# Flask
##########################################################################################
app = Flask(__name__)

@app.route('/')
def index():

    # Сегодняшняя дата и период анализа
    today = date.today().strftime("%d.%m.%Y")
    start_day = all_df["Дата"].min().strftime("%d.%m.%Y")
    end_day = all_df["Дата"].max().strftime("%d.%m.%Y")

    # Доходы
    income_series = pd.to_numeric(table_income, errors='coerce').dropna()
    create_diagram(income_series, "Доходы.png")
    income_df = income_series.reset_index()
    income_df.columns = ["Категория", "Сумма"]
    income_html = income_df.to_html(index=False)
    total_income = income_df["Сумма"].sum()

    # Расходы
    expense_series = pd.to_numeric(table_expense, errors='coerce').dropna().abs()
    create_diagram(expense_series, "Расходы.png")
    expense_df = expense_series.reset_index()
    expense_df.columns = ["Категория", "Сумма"]
    expense_html = expense_df.to_html(index=False)
    total_expense = expense_df["Сумма"].sum()

    balance = total_income - total_expense


    return f"""
    <html>
    <head>
        <meta charset="utf-8">
        <title>МоиФинансы</title>
        <style>
            body {{
                font-family: 'Segoe UI';
                margin: 0;
                padding: 20px;
                background: #f0f2f5;
            }}
            header {{
                background: linear-gradient(135deg, #4CAF50, #2E7D32);
                color: white;
                padding: 30px;
                border-radius: 12px;
                box-shadow: 0 4px 15px rgba(0,0,0,0.2);
                margin-bottom: 30px;
                text-align: center;
            }}
            h1 {{
                margin: 0 0 10px 0;
                font-size: 36px;
            }}
            .dates {{
                margin: 0;
                opacity: 0.9;
                font-size: 16px;
            }}
            h2 {{
                text-align: center;
                color: #333;
            }}
            table {{
                width: 100%;
                border-collapse: collapse;
                background: white;
                border-radius: 8px;
                overflow: hidden;
                box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            }}
            .table th {{
                text-align: center;
                background: #4CAF50;
                color: white;
                padding: 10px;
            }}
            .table td {{
                padding: 8px;
                text-align: left;
            }}
            .table tr:nth-child(even) {{
                background: #f9f9f9;
            }}
            
            .summary {{
                text-align: center;
                font-size: 20px;
                margin-top: 30px;
                padding: 20px;
                background: white;
                border-radius: 12px;
                box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            }}
            .green {{ color: #4CAF50; font-weight: bold; }}
            .red {{ color: #E53935; font-weight: bold; }}
            .blue {{ color: #1E88E5; font-weight: bold; }}
        </style>
        </head>
        <body>
            <header>
                <h1>МоиФинансы</h1>
                <p class="dates">Дата анализа: {today} | Период: {start_day} – {end_day}</p>
            </header>
        
            <div style="display: flex; justify-content: center; gap: 40px;">
                <div>
                    <h2>Расходы</h2>
                    <img src = "static/Расходы.png">
                    <div class="table">
                        {expense_html}
                    </div>
                </div>
                <div>
                    <h2>Доходы</h2>
                    <img src = "static/Доходы.png">
                    <div class="table">
                        {income_html}
                    </div>
                </div>
            </div>
            <div class="summary">
                <p>Доход: <span class="green">+{total_income:.0f} ₽</span></p>
                <p>Расход: <span class="red">{total_expense:.0f} ₽</span></p>
                <p>Баланс: <span class="blue">{balance:.0f} ₽</span></p>
            </div>
        </body>
    </html>"""


if __name__ == '__main__':
    app.run(debug=True)


