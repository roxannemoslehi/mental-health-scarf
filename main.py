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
            r = requests.post('put scarf url here', data = "love")
        else:
            pass

    # display happy.html page

    return render_template('happy.html')

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
