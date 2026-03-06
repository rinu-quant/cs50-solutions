-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT year, month, day,description
FROM crime_scene_reports
WHERE description LIKE '%CS50 duck%';


SELECT license_plate
FROM bakery_security_logs
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute BETWEEN 15 AND 25
  AND activity = 'exit';



SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2025
      AND month = 7
      AND day = 28
      AND hour = 10
      AND minute BETWEEN 15 AND 25
      AND activity = 'exit' );




SELECT account_number
FROM atm_transactions
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND atm_location LIKE '%Leggett%'
  AND transaction_type = 'withdraw';





SELECT people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2025
      AND month = 7
      AND day = 28
      AND atm_location LIKE '%Leggett%'
      AND transaction_type = 'withdraw'
);




SELECT caller
FROM phone_calls
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND duration < 60;




SELECT name
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2025
      AND month = 7
      AND day = 28
      AND duration < 60
);




SELECT name
FROM people
WHERE name IN (
        SELECT name
        FROM people
        JOIN bank_accounts ON people.id = bank_accounts.person_id
        WHERE bank_accounts.account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2025
              AND month = 7
              AND day = 28
              AND atm_location LIKE '%Leggett%'
              AND transaction_type = 'withdraw'
        )
    )
  AND name IN (
        SELECT name
        FROM people
        WHERE license_plate IN (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2025
              AND month = 7
              AND day = 28
              AND hour = 10
              AND minute BETWEEN 15 AND 25
              AND activity = 'exit'
        )
    )
  AND name IN (
        SELECT name
        FROM people
        WHERE phone_number IN (
            SELECT caller
            FROM phone_calls
            WHERE year = 2025
              AND month = 7
              AND day = 28
              AND duration < 60
        )
    );






SELECT name, passport_number
FROM people
WHERE name IN ('Bruce', 'Diana');




SELECT passengers.passport_number, airports.city
FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE passengers.passport_number IN (
    SELECT passport_number
    FROM people
    WHERE name IN ('Bruce', 'Diana')
)
AND flights.year = 2025
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour ASC, flights.minute ASC
LIMIT 1;






SELECT name, phone_number
FROM people
WHERE passport_number = 5773159633;




SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE caller = '(367) 555-5533'
      AND year = 2025
      AND month = 7
      AND day = 28
      AND duration < 60
);




