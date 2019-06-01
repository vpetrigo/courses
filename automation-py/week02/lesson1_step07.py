import math

from selenium import webdriver


def calc(x):
    return str(math.log(abs(12 * math.sin(int(x)))))


def print_answer(remote: webdriver.Remote):
    alert = remote.switch_to.alert
    print(alert.text.split()[-1])
    alert.accept()


browser = webdriver.Chrome()
link = "http://suninjuly.github.io/get_attribute.html"
browser.get(link)

try:
    x_element = browser.find_element_by_id("treasure").get_attribute("valuex")
    browser.find_element_by_id("answer").send_keys(calc(x_element))
    elements_to_select = tuple(("#robotCheckbox", "#robotsRule", "button.btn.btn-default"))

    for elem in elements_to_select:
        browser.find_element_by_css_selector(elem).click()

    print_answer(browser)
finally:
    browser.quit()
