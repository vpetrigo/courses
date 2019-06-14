import math
import stepik
import os

from selenium import webdriver
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.common.by import By


def calc(x):
    return str(math.log(abs(12 * math.sin(int(x)))))


def print_answer(remote: webdriver.Remote):
    alert = remote.switch_to.alert
    ans = alert.text.split()[-1]
    print(ans)
    alert.accept()

    return ans


link = "http://suninjuly.github.io/explicit_wait2.html"
browser = webdriver.Chrome()
browser.get(link)

try:
    WebDriverWait(browser, 10).until(
        expected_conditions.text_to_be_present_in_element((By.ID, "price"),
                                                          "10000"))
    browser.find_element_by_id("book").click()
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
        "https://stepik.org/lesson/181384/step/8?unit=156009").send_answer(
            answer)
finally:
    browser.quit()
