from flask import Flask, render_template,request, redirect, url_for
from flask_bootstrap import Bootstrap
import requests

app = Flask(__name__)
Bootstrap(app)
# we are able to make 2 different requests on our webpage
# GET = we just type in the url
# POST = some sort of form submission like a button

global stress_count  #global stress count
stress_count = 0
global is_pressed
is_pressed = 0
global changed
changed = 0

@app.route('/')
def index():
    return render_template('index.html', count=stress_count)

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/send_love', methods=["POST", "GET"])
def send_love():


    # if send love button is pressed, make post request to scarf
    if request.method == "POST":
        if request.form['submit'] == 'love':
            print 'SENT LOVE!'
            global is_pressed
            is_pressed = 1
            print is_pressed
        else:
            pass

    # display happy.html page

    return render_template('happy.html')

@app.route('/pressed', methods=["POST", "GET"])
def pressed():
    global is_pressed
    global changed

    if request.method == "POST":
        print "GOT POST REQUEST FOR /PRESSED"
        print "Pressed?: ", is_pressed
        if (request.get_data() == "checking"):
            if (is_pressed == 1):
                if changed == 5:
                    # made succesful post request, change pressed back to unpressed
                    is_pressed = 0
                    print "setting button to unpressed"
                    changed = 0
                else:
                    changed+= 1
                    pass
            else:
                print "button isn't pressed"
                pass
        else:
            pass


    return render_template('pressed.html', pressed=is_pressed)


# feather will send post request to /stressed page
# when we get post request, we update counter/main page
@app.route('/stressed', methods = ['POST'])
def im_stressed():

    if request.method == 'POST':
        if request.data == "love":
            global stress_count
            stress_count +=1
            print "POST REQUEST made from scarf"
            print "Count updated:", stress_count

    # display index.html page
    return render_template('index.html', count=stress_count)


if __name__ == "__main__":


    # lets launch our webpage!
    # do 0.0.0.0 so that we can log into this webpage
    # using another computer on the same network later
    app.run('0.0.0.0', debug=True)
