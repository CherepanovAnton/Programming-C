from pytest_check import check
from main import (category_income, category_expense, parse_alfa, parse_sber,
                  parse_tbank, parse_vtb)

def test_category_income():
    check.equal(category_income("Перевод от Ч. Михаил Владимирович"), "Родители")
    check.equal(category_income("Соболева Наталья Сергеевна"), "Родители")
    check.equal(category_income("Перевод от С. Валентина Трофимовна"), "Бабушка")
    check.equal(category_income("Стипендия учащимся"), "Стипендия")
    check.equal(category_income("Проценты по вкладу"), "Проценты")
    check.equal(category_income("Перевод от Александр К."), "Переводы")

def test_category_expense():
    check.equal(category_expense("YARCHE NOVOSIBIRSK RUS"), "Продукты")
    check.equal(category_expense("PYATEROCHKA"), "Продукты")
    check.equal(category_expense("SOLNECHNYJ DEN"), "Фастфуд")
    check.equal(category_expense("BURGER KING"), "Фастфуд")
    check.equal(category_expense("TPP_METRO_NOVOSIBIRSK"), "Транспорт")
    check.equal(category_expense("t2_SBP"), "Связь")

def test_parse_alfa():
    df = parse_alfa("data/Alfa-Bank.csv")
    check.equal(list(df.columns), ["Дата", "Сумма", "Описание"])
    check.greater(len(df), 0)

def test_parse_sber():
    df = parse_sber("data/SberBank.csv")
    check.equal(list(df.columns), ["Дата", "Сумма", "Описание"])
    check.greater(len(df), 0)

def test_parse_vtb():
    df = parse_vtb("data/VTB.xlsx")
    check.equal(list(df.columns), ["Дата", "Сумма", "Описание"])
    check.greater(len(df), 0)

def test_parse_tbank():
    df = parse_tbank("data/TBank.csv")
    check.equal(list(df.columns), ["Дата", "Сумма", "Описание"])
    check.greater(len(df), 0)
