import math
import os
import stepik

from selenium import webdriver
from selenium.webdriver.support.wait import WebDriverWait


def calc(x):
    return str(math.log(abs(12 * math.sin(int(x)))))


def print_answer(remote: webdriver.Remote):
    alert = remote.switch_to.alert
    ans = alert.text.split()[-1]
    print(ans)
    alert.accept()

    return ans


link = "http://suninjuly.github.io/alert_accept.html"
browser = webdriver.Chrome()
browser.get(link)

try:
    browser.find_element_by_css_selector("[type = \"submit\"]").click()
    browser.switch_to.alert.accept()
    WebDriverWait(browser,
                  3).until(lambda x: x.find_element_by_id("input_value"))
    browser.find_element_by_id("answer").send_keys(
        calc(browser.find_element_by_id("input_value").text))
    browser.find_element_by_css_selector("[type = \"submit\"]").click()
    answer = print_answer(browser)

    stepik.SeleniumAuth(os.getenv("login"), os.getenv("password"),
                        browser).auth()
    stepik.SeleniumAnswer(
        browser,
        "https://stepik.org/lesson/184253/step/4?unit=158843").send_answer(
            answer)
finally:
    browser.quit()
