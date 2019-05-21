import math

from selenium import webdriver

secret_link: str = str(math.ceil(math.pow(math.pi, math.e)*10000))
browser = webdriver.Chrome()

browser.get("http://suninjuly.github.io/find_link_text")
link = browser.find_element_by_link_text(secret_link)
link.click()

input1 = browser.find_element_by_tag_name("input")
input1.send_keys("Ivan")
input2 = browser.find_element_by_name("last_name")
input2.send_keys("Petrov")
input3 = browser.find_element_by_class_name("city")
input3.send_keys("Smolensk")
input4 = browser.find_element_by_id("country")
input4.send_keys("Russia")
button = browser.find_element_by_css_selector("button.btn")
button.click()

alert = browser.switch_to.alert
alert_text = alert.text
# validate the alert text
alert.accept()

print(alert_text.split()[-1])

browser.close()
browser.quit()
