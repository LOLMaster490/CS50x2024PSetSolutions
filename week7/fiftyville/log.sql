-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get info from crime scene reports
SELECT * FROM crime_scene_reports;
-- Theft took place at July 28 2023 10:15 on Humphrey Street. Interview transcripts available.
-- Get info from interview transcripts on the day of robbery
SELECT * FROM interviews WHERE year = '2023' AND month = '7' AND day = '28';
-- Thief got into a car in bakery parking lot within 10 minutes of robbery. TODO: LOOK AT CARS LEAVING BAKERY PARKING LOT WITHIN 10:15 - 10:30.
-- Thief withdrew money at an ATM on Leggett Street in the morning (Seen by Eugene on the way to Emma's bakery). TODO: CHECK ATM WITHDRAWALS AT LEGGETT STREET
-- After leaving the bakery thief made a phone call for less than 1min. TODO: CHECK CALL LOGS
-- Thief took earliest flight out of fiftyville the next day. TODO: CHECK FLIGHT LOG
-- Robert and Patrick took a rooster to Paris

-- Check cars leaving bakery parking lot on day of the robbery before 10:30am
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30;
-- Eight licence plates 0NTHK55 322W7JE L93JTIZ G412CB7 4328GD8 6P58WS2 94KL13X 5P2BI95

-- Check for calls around time of robbery shorter than 1 minute
SELECT * FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;

-- Check ATM withdrawals at Leggett Street
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Check for fiftyville airport code
SELECT * FROM airports WHERE city = 'Fiftyville';
-- CSF / Fiftyville Regional Airport

-- Check for first flight leaving Fiftyville at 29/07/2023
SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2023 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour, minute ASC LIMIT 1;

-- Find destination airport
SELECT * FROM airports WHERE id = 4;
-- LGA / LaGuardia Airport / New York City

-- List passengers on that flight
SELECT * FROM passengers WHERE flight_id = 36;

-- Search those people by passport number
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- Filter bakery security logs to only include people who were present on flight with id 36
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30 AND license_plate IN (
    SELECT license_plate FROM people WHERE passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36));

-- Filter for calls shorter than 1 min on day of the robbery and made by people who were on flight with id 36
SELECT * FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (
    SELECT phone_number FROM people WHERE passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36));

SELECT * FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (
        SELECT phone_number FROM people WHERE passport_number IN (
            SELECT passport_number FROM passengers WHERE flight_id = 36))) AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30 AND license_plate IN (
    SELECT license_plate FROM people WHERE passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36)));

-- Three people remaining, search if any of them withdrew money at Leggett Street

SELECT * FROM bank_accounts WHERE person_id IN (
    SELECT id FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (
        SELECT phone_number FROM people WHERE passport_number IN (
            SELECT passport_number FROM passengers WHERE flight_id = 36))) AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30 AND license_plate IN (
    SELECT license_plate FROM people WHERE passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36))));

-- Got singular person ID - 686048, find out who that is

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE person_id IN (
    SELECT id FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (
        SELECT phone_number FROM people WHERE passport_number IN (
            SELECT passport_number FROM passengers WHERE flight_id = 36))) AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30 AND license_plate IN (
    SELECT license_plate FROM people WHERE passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36)))));

-- Bruce is the thief

-- Check who Bruce called after the robbery

SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE person_id IN (
    SELECT id FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (
        SELECT phone_number FROM people WHERE passport_number IN (
            SELECT passport_number FROM passengers WHERE flight_id = 36))) AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30 AND license_plate IN (
    SELECT license_plate FROM people WHERE passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36)))))) AND year = 2023 AND month = 7 AND day = 28 AND duration < 60;

-- Got one number

-- Check who receiver number belongs to
SELECT * FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE caller IN (
        SELECT phone_number FROM people WHERE id IN (
            SELECT person_id FROM bank_accounts WHERE person_id IN (
    SELECT id FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (
        SELECT phone_number FROM people WHERE passport_number IN (
            SELECT passport_number FROM passengers WHERE flight_id = 36))) AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30 AND license_plate IN (
    SELECT license_plate FROM people WHERE passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = 36)))))) AND year = 2023 AND month = 7 AND day = 28 AND duration < 60);

-- Robin was the accomplice
