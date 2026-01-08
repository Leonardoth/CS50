import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, transaction, addToHistory

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute(
        "Select symbol, quantity FROM portfolio WHERE user_id == ?", session["user_id"])
    userCash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]
    totalInStocks = 0
    for item in portfolio:
        price = lookup(item["symbol"])["price"]
        item["price"] = price
        totalInStocks += price * item["quantity"]
    total = userCash + totalInStocks
    return render_template("index.html", portfolio=portfolio, totalInStocks=totalInStocks, cash=userCash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Invalid symbol.", 400)
        quantity = request.form.get("shares")
        status = transaction("buy", db, user_id, symbol, quantity)
        if status["status"]:
            return redirect("/")
        else:
            return apology(status["message"])

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userHistory = db.execute(
        "SELECT * FROM history WHERE user_id == ? ORDER BY transacted DESC", session["user_id"])
    return render_template("history.html", history=userHistory)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quoted = lookup(request.form.get("symbol"))
        if not quoted:
            return apology("Invalid symbol.", 400)
        return render_template("quote.html", quoted=quoted, isQuoted=True)
    return render_template("quote.html", isQuoted=False)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username").lower()
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("Invalid Username", 400)
        if not password:
            return apology("Missing password", 400)
        if not confirmation:
            return apology("Passwords don't match", 400)
        if password != confirmation:
            return apology("Passwords don't match", 400)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?,?)",
                       username, generate_password_hash(password))
            return redirect("/login")
        except ValueError:
            return apology("Username already exists!", 400)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        quantity = request.form.get("shares")
        status = transaction("sell", db, user_id, symbol, quantity)
        if status["status"]:
            return redirect("/")
        else:
            return apology(status["message"])
    options = db.execute(
        "SELECT symbol FROM portfolio WHERE user_id == ? AND quantity > 0", session["user_id"])
    return render_template("sell.html", options=options)


@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changePassword():
    if request.method == "POST":
        userSentPassword = request.form.get("password")
        serverPassword = db.execute("SELECT hash FROM users WHERE id == ?",
                                    session["user_id"])[0]["hash"]
        if (check_password_hash(serverPassword, userSentPassword)):
            newPassword = request.form.get("newpassword")
            confirmPassword = request.form.get("confirmation")
            if (newPassword == confirmPassword):
                newPassword = generate_password_hash(newPassword)
                db.execute("UPDATE users SET hash = ? WHERE id == ?",
                           newPassword, session["user_id"])
                return redirect("/")
            return apology("Confirmation must match new password.")
        return apology("Wrong password.")
    return render_template("changepassword.html")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "POST":
        value = request.form.get("value")
        try:
            value = int(value)
        except ValueError:
            return apology("Wrong value format.")
        if value <= 0:
            return apology("Invalid deposit.")
        userCash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]
        newCash = userCash + value
        addToHistory(db, type="Deposit", symbol="CASH", shares="1", price=value)
        db.execute("UPDATE users SET cash = ROUND (?, 2) WHERE id == ?",
                   newCash, session["user_id"])
        return redirect("/")
    return render_template("deposit.html")
