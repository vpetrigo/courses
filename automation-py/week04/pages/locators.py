from selenium.webdriver.common.by import By


class MainPageLocators(object):
    REGISTRATION_LINK = (By.CSS_SELECTOR, "#registration_link")
    LOGIN_LINK = (By.CSS_SELECTOR, "#login_link")
