#include "WebPage.h"

extern const char index_html[] PROGMEM =
    R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Porch Light Controller</title>
  <style>
    /* Basic styling to make it look clean on a phone or desktop */
    body {
      font-family: sans-serif;
      text-align: center;
      margin-top: 50px;
      background-color: #f4f4f9;
    }
    .btn {
      padding: 15px 30px;
      font-size: 18px;
      font-weight: bold;
      background-color: #007bff;
      color: white;
      border: none;
      border-radius: 8px;
      cursor: pointer;
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
    }
    .btn:active {
      background-color: #0056b3;
      transform: translateY(2px);
    }
  </style>
</head>
<body>

  <h1>Porch Light</h1>
  
  <!-- The button triggers the JavaScript function when clicked -->
  <button class="btn" onclick="lightOverride()">Turn On Temporarily (10s)</button>

  <script>
    function lightOverride() {
      fetch('/lightOverride')
        .then(response => {
          if (response.ok) {
            console.log("Request sent successfully!");
          }
        })
        .catch(error => {
          console.error("Network error or server offline:", error);
        });
    }
  </script>

</body>
</html>)rawliteral";
