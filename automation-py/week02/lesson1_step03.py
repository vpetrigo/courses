from selenium import webdriver
from selenium.webdriver.support.ui import Select


def print_answer(remote: webdriver.Remote):
    alert = remote.switch_to.alert
    print(alert.text.split()[-1])
    alert.accept()


# link = "http://suninjuly.github.io/selects1.html"
link = "http://suninjuly.github.io/selects2.html"
browser = webdriver.Chrome()
browser.get(link)

try:
    nums_id = tuple(("num1", "num2"))
    result = sum(map(int, (browser.find_element_by_id(num_id).text for num_id in nums_id)))
    select = Select(browser.find_element_by_id("dropdown"))
    select.select_by_value(str(result))
    browser.find_element_by_css_selector(".btn.btn-default").click()
    print_answer(browser)
finally:
    browser.quit()
