from selenium import webdriver
from selenium.webdriver.support.wait import WebDriverWait

link = "http://suninjuly.github.io/registration1.html"
# link = "http://suninjuly.github.io/registration2.html"
browser = webdriver.Chrome()
browser.get(link)

try:
    # Ваш код, который заполняет обязательные поля
    first_required = browser.find_element_by_css_selector("div.first_block .form-control.first")
    second_required = browser.find_element_by_css_selector("div.first_block .form-control.second")
    third_required = browser.find_element_by_css_selector("div.first_block .form-control.third")
    required_input = ["Name", "Surname", "a@a.au"]

    for input_element, test_input in zip((first_required, second_required, third_required), required_input):
        input_element.send_keys(test_input)

    # Отправляем заполненную форму
    button = browser.find_element_by_css_selector("button.btn")
    button.click()

    # Проверяем, что смогли зарегистрироваться
    # ждем загрузки страницы
    WebDriverWait(browser, 3).until(lambda x: x.find_element_by_tag_name("h1"))

    # находим элемент, содержащий текст
    welcome_text_elt = browser.find_element_by_tag_name("h1")
    # записываем в переменную welcome_text текст из элемента welcome_text_elt
    welcome_text = welcome_text_elt.text

    # с помощью assert проверяем, что ожидаемый текст совпадает с текстом на странице сайта
    assert "Поздравляем! Вы успешно зарегистировались!" == welcome_text
finally:
    browser.close()
    browser.quit()
