-- Keep a log of any SQL queries you execute as you solve the mystery.

-- I looked for all the tables present
.tables

-- Got the crime_scene_reports table schema
.schema crime_scene_reports

-- First I'll get the crime_scene_reports from the day
SELECT day,month,description,street
FROM crime_scene_reports
WHERE year = 2024
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

-- From that we get
-- Time: 10:15am
-- Place: Humphrey Street Bakery
-- Witnesses: 3

-- Get the interviews schema
.schema interviews

-- We got every interview from the day
SELECT id, name, transcript
FROM interviews
WHERE year = 2024
AND month = 7
AND day = 28;

-- From that we get
-- Witness Ru. Says: Ten minutes within the theft, thief got into a car in the bakery parking lot.
-- Witness E. Says: Thief withdrew money from the ATM on Leggett Street on the morning of the 28th
-- Witness Ra. Says: Thief called someone, talked less than a minute and asked them to buy the earliest flight out of fiftyville in the 29th.

-- Plan:
-- Check for security footage of the bakery's parking lot between 10:15 and 10:25
-- Check for ATM logs for the morning of 28th
-- Check for the phone logs right after the theft, short call, find who was the person on the receiving end and to what is the destination of the ticket

-- Get Schema
.schema bakery_security_logs

-- We get every event from the bakery_security logs in the day and hour
SELECT minute, activity, license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2024
AND hour = 10;

-- We get more specific to the exits and time
SELECT minute, activity, license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2024
AND hour = 10
AND activity = 'exit'
AND minute > 10
AND minute < 30;

-- What we know now:
-- Time: 10:15am
-- Place: Humphrey Street Bakery
-- Witnesses: 3
    -- Witness Ru. Says: Ten minutes within the theft, thief got into a car in the bakery parking lot.
    -- Witness E. Says: Thief withdrew money from the ATM on Leggett Street on the morning of the 28th
    -- Witness Ra. Says: Thief called someone, talked less than a minute and asked them to buy the earliest flight out of fiftyville in the 29th.
-- Possible Plates:
-- +--------+----------+---------------+
-- | minute | activity | license_plate |
-- +--------+----------+---------------+
-- | 16     | exit     | 5P2BI95       |
-- | 18     | exit     | 94KL13X       |
-- | 18     | exit     | 6P58WS2       |
-- | 19     | exit     | 4328GD8       |
-- | 20     | exit     | G412CB7       |
-- | 21     | exit     | L93JTIZ       |
-- | 23     | exit     | 322W7JE       |
-- | 23     | exit     | 0NTHK55       |
-- +--------+----------+---------------+

-- Check for ATM logs for the morning of 28th
.schema atm_transactions

-- Get every transaction of that atm of the day
SELECT account_number, transaction_type, amount
FROM atm_transactions
WHERE year = 2024
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street';

-- Get every withdraw account number
SELECT account_number
FROM atm_transactions
WHERE year = 2024
AND month = 7
AND day = 28 AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';


-- What we know now:
-- Time: 10:15am
-- Place: Humphrey Street Bakery
-- Witnesses: 3
    -- Witness Ru. Says: Ten minutes within the theft, thief got into a car in the bakery parking lot.
    -- Witness E. Says: Thief withdrew money from the ATM on Leggett Street on the morning of the 28th
    -- Witness Ra. Says: Thief called someone, talked less than a minute and asked them to buy the earliest flight out of fiftyville in the 29th.
-- Possible Plates:
    -- +--------+----------+---------------+
    -- | minute | activity | license_plate |
    -- +--------+----------+---------------+
    -- | 16     | exit     | 5P2BI95       |
    -- | 18     | exit     | 94KL13X       |
    -- | 18     | exit     | 6P58WS2       |
    -- | 19     | exit     | 4328GD8       |
    -- | 20     | exit     | G412CB7       |
    -- | 21     | exit     | L93JTIZ       |
    -- | 23     | exit     | 322W7JE       |
    -- | 23     | exit     | 0NTHK55       |
    -- +--------+----------+---------------+
-- Possible Account Number:
    -- +----------------+
    -- | account_number |
    -- +----------------+
    -- | 28500762       |
    -- | 28296815       |
    -- | 76054385       |
    -- | 49610011       |
    -- | 16153065       |
    -- | 25506511       |
    -- | 81061156       |
    -- | 26013199       |
    -- +----------------+

-- Get Name from everyone that used the atm Withdrawn
SELECT name, bank_accounts.account_number
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street');

-- People that took money from the atm
    -- +---------+----------------+
    -- |  name   | account_number |
    -- +---------+----------------+
    -- | Bruce   | 49610011       |
    -- | Diana   | 26013199       |
    -- | Brooke  | 16153065       |
    -- | Kenny   | 28296815       |
    -- | Iman    | 25506511       |
    -- | Luca    | 28500762       |
    -- | Taylor  | 76054385       |
    -- | Benista | 81061156       |
    -- +---------+----------------+

-- Check for the phone logs right after the theft, short call, find who was the person on the receiving end and to what is the destination of the ticket
.schema phone_calls

-- We check for every phone call for the day that lasted less than one minute
SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2024
AND month = 7
AND day = 28
AND duration <= 60;

-- What we know now:
-- Time: 10:15am
-- Place: Humphrey Street Bakery
-- Witnesses: 3
    -- Witness Ru. Says: Ten minutes within the theft, thief got into a car in the bakery parking lot.
    -- Witness E. Says: Thief withdrew money from the ATM on Leggett Street on the morning of the 28th
    -- Witness Ra. Says: Thief called someone, talked less than a minute and asked them to buy the earliest flight out of fiftyville in the 29th.

-- Possible Plates:
    -- +--------+----------+---------------+
    -- | minute | activity | license_plate |
    -- +--------+----------+---------------+
    -- | 16     | exit     | 5P2BI95       |
    -- | 18     | exit     | 94KL13X       |
    -- | 18     | exit     | 6P58WS2       |
    -- | 19     | exit     | 4328GD8       |
    -- | 20     | exit     | G412CB7       |
    -- | 21     | exit     | L93JTIZ       |
    -- | 23     | exit     | 322W7JE       |
    -- | 23     | exit     | 0NTHK55       |
    -- +--------+----------+---------------+

-- Possible Account Number:
    -- +----------------+
    -- | account_number |
    -- +----------------+
    -- | 28500762       |
    -- | 28296815       |
    -- | 76054385       |
    -- | 49610011       |
    -- | 16153065       |
    -- | 25506511       |
    -- | 81061156       |
    -- | 26013199       |
    -- +----------------+

-- Possible Phone Numbers
    -- +----------------+----------------+----------+
    -- |     caller     |    receiver    | duration |
    -- +----------------+----------------+----------+
    -- | (130) 555-0289 | (996) 555-8899 | 51       |
    -- | (499) 555-9472 | (892) 555-8872 | 36       |
    -- | (367) 555-5533 | (375) 555-8161 | 45       |
    -- | (609) 555-5876 | (389) 555-5198 | 60       |
    -- | (499) 555-9472 | (717) 555-1342 | 50       |
    -- | (286) 555-6063 | (676) 555-6554 | 43       |
    -- | (770) 555-1861 | (725) 555-3243 | 49       |
    -- | (031) 555-6622 | (910) 555-3251 | 38       |
    -- | (826) 555-1652 | (066) 555-9701 | 55       |
    -- | (338) 555-6650 | (704) 555-2131 | 54       |
    -- +----------------+----------------+----------+


-- I'll try to cross data from what I have:

-- Get name and phone number from every one that was caught in the bakery security camera
SELECT name, phone_number
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2024
    AND hour = 10
    AND activity = 'exit'
    AND minute > 10
    AND minute < 30);

-- Suspects
    -- +---------+----------------+
    -- |  name   |  phone_number  |
    -- +---------+----------------+
    -- | Vanessa | (725) 555-4692 |
    -- | Barry   | (301) 555-4174 |
    -- | Iman    | (829) 555-5269 |
    -- | Sofia   | (130) 555-0289 |
    -- | Luca    | (389) 555-5198 |
    -- | Diana   | (770) 555-1861 |
    -- | Kelsey  | (499) 555-9472 |
    -- | Bruce   | (367) 555-5533 |
    -- +---------+----------------+

-- I'll cross this Phone numbers and Plates with the ones from callers of the previous step

SELECT name, phone_number
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2024
    AND hour = 10
    AND activity = 'exit'
    AND minute > 10
    AND minute < 30)
    AND
    phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND duration <= 60);

-- Suspects
    -- +--------+----------------+
    -- |  name  |  phone_number  |
    -- +--------+----------------+
    -- | Sofia  | (130) 555-0289 |
    -- | Diana  | (770) 555-1861 |
    -- | Kelsey | (499) 555-9472 |
    -- | Bruce  | (367) 555-5533 |
    -- +--------+----------------+

-- Finding out possible accomplice (that bought the ticket)
SELECT name, receiver as phone, caller as called_by
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE caller IN
    (SELECT phone_number
    FROM people
    WHERE license_plate
    IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28
        AND month = 7
        AND year = 2024
        AND hour = 10
        AND activity = 'exit'
        AND minute > 10
        AND minute < 30)
        AND
        phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2024
        AND month = 7
        AND day = 28
        AND duration <= 60))
    AND year = 2024
    AND month = 7
    AND day = 28
    AND duration <= 60;


-- Possible Accomplices
    -- +---------+----------------+----------------+
    -- |  name   |     phone      |   called_by    |
    -- +---------+----------------+----------------+
    -- | Jack    | (996) 555-8899 | (130) 555-0289 |
    -- | Larry   | (892) 555-8872 | (499) 555-9472 |
    -- | Robin   | (375) 555-8161 | (367) 555-5533 |
    -- | Melissa | (717) 555-1342 | (499) 555-9472 |
    -- | Philip  | (725) 555-3243 | (770) 555-1861 |
    -- +---------+----------------+----------------+

-- What was the first flight of the next day?
SELECT id, hour,minute,origin_airport_id, destination_airport_id
FROM flights
WHERE year = 2024
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1;

-- First Flight in the morning
    -- +----+------+--------+-------------------+------------------------+
    -- | id | hour | minute | origin_airport_id | destination_airport_id |
    -- +----+------+--------+-------------------+------------------------+
    -- | 36 | 8    | 20     | 8                 | 4                      |
    -- +----+------+--------+-------------------+------------------------+

-- Find destination of flight
SELECT abbreviation, full_name, city
FROM airports
WHERE id = 4;
    -- +--------------+-------------------+---------------+
    -- | abbreviation |     full_name     |     city      |
    -- +--------------+-------------------+---------------+
    -- | LGA          | LaGuardia Airport | New York City |
    -- +--------------+-------------------+---------------+

-- Only get the city
SELECT city
FROM airports
WHERE id = 4;

-- Thief's Destination city
    -- +---------------+
    -- |     city      |
    -- +---------------+
    -- | New York City |
    -- +---------------+

-- Next steps
-- Find who was in the flight 36
-- Who bought the ticket

-- Get who was in the flight 36, took money from the atm, left the bakery parking lot driving a car, was in a call that lasted less than a minute
SELECT name, phone_number, passengers.seat
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE people.passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36)
AND people.name IN (
    SELECT name
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28
        AND month = 7
        AND year = 2024
        AND hour = 10
        AND activity = 'exit'
        AND minute > 10
        AND minute < 30)
    AND phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2024
        AND month = 7
        AND day = 28
        AND duration <= 60)
    AND id IN (
    SELECT id
    FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE bank_accounts.account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2024
        AND month = 7
        AND day = 28
        AND transaction_type = 'withdraw'
        AND atm_location = 'Leggett Street'))
);


-- Bruce was in the earliest flight in the next day, talked on the phone for less than a minute and withdrew money from the atm on Leggett Street.
    -- +-------+----------------+------+
    -- | name  |  phone_number  | seat |
    -- +-------+----------------+------+
    -- | Bruce | (367) 555-5533 | 4A   |
    -- +-------+----------------+------+

-- Get who was in the call with Bruce
SELECT name, receiver as phone, caller as called_by
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE caller IN
    (SELECT phone_number
    FROM people
    WHERE license_plate
    IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28
        AND month = 7
        AND year = 2024
        AND hour = 10
        AND activity = 'exit'
        AND minute > 10
        AND minute < 30)
        AND
        phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2024
        AND month = 7
        AND day = 28
        AND duration <= 60))
    AND year = 2024
    AND month = 7
    AND day = 28
    AND duration <= 60
    AND caller = '(367) 555-5533';

-- Accomplice:
    -- +-------+----------------+----------------+
    -- | name  |     phone      |   called_by    |
    -- +-------+----------------+----------------+
    -- | Robin | (375) 555-8161 | (367) 555-5533 |
    -- +-------+----------------+----------------+
