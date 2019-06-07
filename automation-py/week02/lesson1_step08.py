import os

from selenium import webdriver


def print_answer(remote: webdriver.Remote):
    alert = remote.switch_to.alert
    print(alert.text.split()[-1])
    alert.accept()


link = "http://suninjuly.github.io/file_input.html"
browser = webdriver.Chrome()
browser.get(link)

try:
    input_fields = tuple(
        ('[name="firstname"]', '[name="lastname"]', '[name="email"]', "#file"))
    input_test = tuple(
        ("Ivan", "Ivanov", "ivan@ivanov.io", os.path.abspath(__file__)))
    for elem, input_value in zip(input_fields, input_test):
        browser.find_element_by_css_selector(elem).send_keys(input_value)
    browser.find_element_by_css_selector("button.btn.btn-primary").click()
    print_answer(browser)
finally:
    browser.quit()
