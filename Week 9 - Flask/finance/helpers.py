import requests

from flask import redirect, render_template, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""
    url = f"https://finance.cs50.io/quote?symbol={symbol.upper()}"
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an error for HTTP error responses
        quote_data = response.json()
        return {
            "name": quote_data["companyName"],
            "price": quote_data["latestPrice"],
            "symbol": symbol.upper()
        }
    except requests.RequestException as e:
        print(f"Request error: {e}")
    except (KeyError, ValueError) as e:
        print(f"Data parsing error: {e}")
    return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


def transaction(transactionType, db, user_id, symbol, quantity):
        user_id = session["user_id"]
        if not quantity or not symbol:
            return {"status": False, "message": "Not enough data."}
        try:
            quantity = int(quantity)
        except ValueError:
            return {"status": False, "message": "Quantity must be a number."}
        if quantity <= 0 :
            return {"status": False, "message": "Quantity must be greater than 0."}
        userCash = db.execute("SELECT cash from users WHERE id == ?", user_id)[0]["cash"]
        stock = lookup(symbol)
        if not stock or not stock["name"]:
            return {"status": False, "message": "Invalid Symbol"}
        cost = stock["price"] * quantity
        if transactionType == "buy":
            if userCash >= cost:
                oldQuantity = db.execute("SELECT quantity FROM portfolio WHERE user_id == ? AND symbol == ?", user_id, symbol)
                if oldQuantity:
                    oldQuantity = oldQuantity[0]["quantity"]
                    newQuantity = oldQuantity + quantity
                else:
                    newQuantity = quantity
                db.execute("INSERT INTO portfolio (user_id, symbol, quantity) VALUES (?, ?, ?) ON CONFLICT (user_id, symbol) DO UPDATE SET quantity = ?", user_id, symbol, newQuantity, newQuantity)
                addToHistory(db, symbol, type="Buy", shares= quantity, price=stock["price"])
                cash = userCash - cost
                db.execute("UPDATE users SET cash = ROUND(?,2) WHERE id = ?", cash, user_id)
                return {"status": True, "message": ""}

            return {"status": False, "message": "Insuficcient Credits."}
        elif transactionType == "sell":
            profit = stock["price"]  * quantity
            oldQuantity = db.execute("SELECT quantity FROM portfolio WHERE user_id == ? AND symbol == ?", user_id, symbol)
            if oldQuantity:
                oldQuantity = oldQuantity[0]["quantity"]
                if quantity > oldQuantity:
                    return {"status": False, "message": "Not enough stocks!"}
                newQuantity = oldQuantity - quantity
            else:
                return status(True, "Not enough stocks!")
            db.execute("INSERT INTO portfolio (user_id, symbol, quantity) VALUES (?, ?, ?) ON CONFLICT (user_id, symbol) DO UPDATE SET quantity = ?", user_id, symbol, newQuantity, newQuantity)
            addToHistory(db, symbol, type="Sell", shares= quantity, price=stock["price"])
            cash = userCash + profit
            db.execute("UPDATE users SET cash = ROUND(?,2) WHERE id = ?", cash, user_id)
            return status(True)


def addToHistory(db, symbol, type, shares, price):
    db.execute("INSERT INTO history (user_id, symbol, type, shares, price) VALUES(?, ?, ?, ?, ?)", session["user_id"], symbol, type, shares, price)


def status(status, message = ""):
    return {"status": status, "message" : message}
