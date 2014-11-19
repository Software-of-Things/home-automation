from subprocess import call
from flask import Flask, redirect, render_template


app = Flask(__name__)
PROJECT_HOME = '/home/pi/projects/home-automation/lamp-switch/'


@app.route('/')
def main():
    return render_template('template.html')


@app.route('/on')
def on():
    call([PROJECT_HOME + 'switch', '-m', '1'])
    return redirect('/')


@app.route('/off')
def off():
    call([PROJECT_HOME + 'switch', '-m', '0'])
    return redirect('/')
