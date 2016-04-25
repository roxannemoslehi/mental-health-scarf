from flask import Flask, render_template,request, redirect, url_for
from flask_bootstrap import Bootstrap

app = Flask(__name__)
Bootstrap(app)
# we are able to make 2 different requests on our webpage
# GET = we just type in the url
# POST = some sort of form submission like a button

stress_count = 0 # global stress count

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/send_love', methods = ['POST', 'GET'])
def send_love():

    # if we make a post request on the webpage aka press button then do stuff

    if request.method == 'POST':

        # if send love button is pressed
        if request.form['submit'] == 'love':
            print 'SENT LOVE!'
        else:
            pass

        value = 10
        # sent this as a post request to scarf


    # display happy.html page
    return render_template('happy.html')



# feather will send post request to /stressed page
# when we get post request, we update counter/main page

@app.route('/stressed', methods = ['POST'])
def im_stressed():

    if request.method == 'POST':
        stress_count += 1 # update stress sounter

    # display index.html page
    return render_template('index.html', count=stress_count)


if __name__ == "__main__":
    # lets launch our webpage!
    # do 0.0.0.0 so that we can log into this webpage
    # using another computer on the same network later
    app.run(debug=True)
