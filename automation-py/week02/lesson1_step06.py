import math

from selenium import webdriver


def calc(x):
    return str(math.log(abs(12 * math.sin(int(x)))))


def scroll_to_view(remote: webdriver.Remote, *args):
    remote.execute_script("arguments[0].scrollIntoView(true);", *args)


def print_answer(remote: webdriver.Remote):
    alert = remote.switch_to.alert
    print(alert.text.split()[-1])
    alert.accept()


link = "http://suninjuly.github.io/execute_script.html"
browser = webdriver.Chrome()
browser.get(link)

try:
    input_field = browser.find_element_by_id("answer")
    input_field.send_keys(
        str(calc(browser.find_element_by_id("input_value").text)))
    elements_to_select = tuple(("#robotCheckbox", "#robotsRule"))

    for elem in elements_to_select:
        obj = browser.find_element_by_css_selector(elem)
        scroll_to_view(browser, obj)
        obj.click()

    button = browser.find_element_by_css_selector("button.btn.btn-default")
    scroll_to_view(browser, button)
    button.click()
    print_answer(browser)
finally:
    browser.quit()
