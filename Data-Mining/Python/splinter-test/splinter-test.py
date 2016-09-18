from splinter.browser import Browser  
  
def main():  
    browser = Browser()  
    browser.visit('https://github.com/lijiansong')  
#     browser.fill('q', 'splinter - python acceptance testing for web applications')  
#     button = browser.find_by_name('btnK')  
#     button.click()  
  
#     if browser.is_text_present('splinter.cobrateam.info'):  
#         print 'yes, the official website was found!'  
#     else:  
#         print "No, it wasn't found... We need o improve our SEO techniques"  
#   
      
#     browser.quit()  
      
  
if __name__ == '__main__':  
    main()