from flask import Flask, render_template,request, redirect, url_for

app = Flask(__name__)
# we are able to make 2 different requests on our webpage
# GET = we just type in the url
# POST = some sort of form submission like a button

stress_count = 0 # global stress count

@app.route('/send_love', methods = ['POST'])
def send_love():

    # if we make a post request on the webpage aka press button then do stuff

    if request.method == 'GET':
        value = 10 #

        # if send love button is pressed
        if request.form['submit'] == 'Send Love':
            print 'SEND_LOVE'
        else:
            pass

    # display happy.html page
    return render_template('happy.html', value=value)



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
    app.run(host='0.0.0.0')