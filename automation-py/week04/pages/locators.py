from selenium.webdriver.common.by import By


class BasePageLocators:
    LOGIN_LINK = (By.ID, "login_link")
    LOGIN_LINK_INVALID = (By.ID, "login_link_inv")
    CART_BUTTON = (By.CSS_SELECTOR, ".basket-mini a.btn.btn-default")
    USER_ICON = (By.CLASS_NAME, "icon-user")


class LoginPageLocators:
    LOGIN_BUTTON = (By.ID, "login_link")
    EMAIL_INPUT = (By.NAME, "registration-email")
    PASSWORD_INPUT = (By.NAME, "registration-password1")
    REPEAT_PASSWORD_INPUT = (By.NAME, "registration-password2")
    REGISTER_BUTTON = (By.NAME, "registration_submit")
    LOGIN_FORM = (By.ID, "login_form")
    REGISTER_FORM = (By.ID, "register_form")


class ProductPageLocators:
    BUTTON_ADD_TO_CART = (By.CLASS_NAME, "btn-add-to-basket")
    ADDING_SUCCESS = (By.CSS_SELECTOR, "div.alert-success")
    ALERT_ADDED_TO_CART = (By.CSS_SELECTOR, "div.alertinner strong")
    ALERT_CART_STATUS = (By.CSS_SELECTOR, ".alert-noicon.alert-info p")
    PRICE_VALUE = (By.CLASS_NAME, "price_color")
    PRODUCT_NAME = (By.TAG_NAME, "h1")
    PRODUCT_PRICE = (By.CSS_SELECTOR, "p.price_color")


class CartPageLocators:
    CART_ELEMENT = (By.CLASS_NAME, "basket-items")
    BASKET_EMPTY_TEXT_ELEMENT = (By.CSS_SELECTOR, "div#content_inner > p")
