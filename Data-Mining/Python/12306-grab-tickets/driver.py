import os
from selenium import webdriver
chromedriver = "D:\Python\chromedriver4win1064\chromedriver.exe"
os.environ["webdriver.chrome.driver"] = chromedriver
driver =  webdriver.Chrome(chromedriver)
driver.get("http://stackoverflow.com")
#driver.quit()
