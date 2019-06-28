import pytest
from selenium import webdriver
from selenium.webdriver.chrome.options import Options as ChromeOptions


def pytest_addoption(parser):
    parser.addoption("--language",
                     action="store",
                     default=None,
                     help="Choose language")
    parser.addoption("--browser", help="Choose browser: chrome or firefox")


@pytest.fixture(scope="function")
def browser(request):
    browser_to_use = request.config.getoption("browser", "chrome")
    language_to_use = request.config.getoption("language")
    print(
        f"Run {browser_to_use} browser with {request.config.getoption('language')} language"
    )

    if browser_to_use == "chrome":
        options = ChromeOptions()
        options.add_argument(f"--lang={language_to_use}")
        browser = webdriver.Chrome(options=options)
    elif browser_to_use == "firefox":
        profile = webdriver.FirefoxProfile()
        profile.set_preference("intl.accept_languages", language_to_use)
        browser = webdriver.Firefox(firefox_profile=profile)
    else:
        raise NotImplementedError

    yield browser

    browser.quit()
