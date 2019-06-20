import unittest

from selenium import webdriver
from selenium.webdriver.support.wait import WebDriverWait


class TestRegistration(unittest.TestCase):
    def setUp(self) -> None:
        super().setUp()
        self.browser = webdriver.Chrome()

    def tearDown(self) -> None:
        super().tearDown()
        self.browser.quit()

    def test_registration1(self) -> None:
        link = "http://suninjuly.github.io/registration1.html"
        self.browser.get(link)
        self.__check(self.browser)

    def test_registration2(self) -> None:
        link = "http://suninjuly.github.io/registration2.html"
        self.browser.get(link)
        self.__check(self.browser)

    def __check(self, remote: webdriver.Remote):
        first_required = remote.find_element_by_css_selector(
            "div.first_block .form-control.first")
        second_required = remote.find_element_by_css_selector(
            "div.first_block .form-control.second")
        third_required = remote.find_element_by_css_selector(
            "div.first_block .form-control.third")
        required_input = ["Name", "Surname", "a@a.au"]

        for input_element, test_input in zip(
            (first_required, second_required, third_required), required_input):
            input_element.send_keys(test_input)

        # Отправляем заполненную форму
        button = remote.find_element_by_css_selector("button.btn")
        button.click()

        # Проверяем, что смогли зарегистрироваться
        # ждем загрузки страницы
        WebDriverWait(remote,
                      3).until(lambda x: x.find_element_by_tag_name("h1"))

        # находим элемент, содержащий текст
        welcome_text_elt = remote.find_element_by_tag_name("h1")
        # записываем в переменную welcome_text текст из элемента welcome_text_elt
        welcome_text = welcome_text_elt.text
        expect = "Поздравляем! Вы успешно зарегистировались!"

        # с помощью assert проверяем, что ожидаемый текст совпадает с текстом на странице сайта
        self.assertEqual(expect, welcome_text,
                         f"{welcome_text} is not {expect}")


if __name__ == "__main__":
    unittest.main()
