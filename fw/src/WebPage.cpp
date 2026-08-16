#include "WebPage.h"

extern const char index_html[] PROGMEM =
    R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Porch Light Controller</title>
  <style>
    body {
      font-family: sans-serif;
      text-align: center;
      margin-top: 30px;
      background-color: #f4f4f9;
      color: #333;
    }
    .card {
      background: white;
      border-radius: 10px;
      padding: 20px;
      margin: 15px auto;
      max-width: 350px;
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
    }
    .btn {
      padding: 15px 30px;
      font-size: 16px;
      font-weight: bold;
      background-color: #007bff;
      color: white;
      border: none;
      border-radius: 8px;
      cursor: pointer;
      width: 100%;
      box-sizing: border-box;
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
      margin-top: 10px;
    }
    .btn:active {
      background-color: #0056b3;
      transform: translateY(2px);
    }
    .btn-green {
      background-color: #28a745;
    }
    .btn-green:active {
      background-color: #1e7e34;
    }
    .form-group {
      text-align: left;
      margin-bottom: 15px;
    }
    .form-group label {
      display: block;
      font-weight: bold;
      margin-bottom: 5px;
    }
    .time-inputs {
      display: flex;
      gap: 10px;
      align-items: center;
    }
    .time-inputs input[type="number"] {
      width: 60px;
      padding: 8px;
      font-size: 16px;
      border: 1px solid #ccc;
      border-radius: 4px;
    }
    .checkbox-group {
      display: flex;
      align-items: center;
      gap: 8px;
      margin-bottom: 10px;
      font-weight: normal;
    }
    .checkbox-group input {
      width: 18px;
      height: 18px;
    }
  </style>
</head>
<body>

  <h1>Porch Light</h1>
  
  <!-- Manual Override Section -->
  <div class="card">
    <h2>Manual Control</h2>
    <button class="btn" onclick="lightOverride()">Turn On Temporarily (10s)</button>
  </div>

  <!-- Schedule Update Section -->
  <div class="card">
    <h2>Update Schedule</h2>
    <form id="scheduleForm">
      
      <!-- ON TIME -->
      <div class="form-group">
        <label>Turn ON Time</label>
        <div class="checkbox-group">
          <input type="checkbox" id="useSunset" name="useSunset" onchange="toggleInputs()">
          <label for="useSunset">Use local sunset</label>
        </div>
        <div class="time-inputs">
          <input type="number" id="tomorrowOnHour" name="tomorrowOnHour" placeholder="HH" min="0" max="23"> :
          <input type="number" id="tomorrowOnMinute" name="tomorrowOnMinute" placeholder="MM" min="0" max="59">
        </div>
      </div>

      <hr style="border: 1px solid #eee; margin: 20px 0;">

      <!-- OFF TIME -->
      <div class="form-group">
        <label>Turn OFF Time</label>
        <div class="checkbox-group">
          <input type="checkbox" id="useSunrise" name="useSunrise" onchange="toggleInputs()">
          <label for="useSunrise">Use local sunrise</label>
        </div>
        <div class="time-inputs">
          <input type="number" id="tomorrowOffHour" name="tomorrowOffHour" placeholder="HH" min="0" max="23"> :
          <input type="number" id="tomorrowOffMinute" name="tomorrowOffMinute" placeholder="MM" min="0" max="59">
        </div>
      </div>

      <button type="button" class="btn btn-green" onclick="submitSchedule()">Save Schedule</button>
    </form>
  </div>

  <script>
    // Temporarily turn on light
    function lightOverride() {
      fetch('/lightOverride')
        .then(response => {
          if (response.ok) alert("Light override activated!");
        })
        .catch(error => console.error("Error:", error));
    }

    // Disable number inputs if the respective sunrise/sunset checkbox is checked
    function toggleInputs() {
      const isSunset = document.getElementById('useSunset').checked;
      document.getElementById('tomorrowOnHour').disabled = isSunset;
      document.getElementById('tomorrowOnMinute').disabled = isSunset;

      const isSunrise = document.getElementById('useSunrise').checked;
      document.getElementById('tomorrowOffHour').disabled = isSunrise;
      document.getElementById('tomorrowOffMinute').disabled = isSunrise;
    }

    // Submit the schedule form using standard URL-encoded format (non-json)
    function submitSchedule() {
      const form = document.getElementById('scheduleForm');
      const formData = new FormData(form);
      
      // URLSearchParams automatically converts FormData into application/x-www-form-urlencoded
      // Note: Unchecked checkboxes are automatically omitted by FormData, which matches your C++ logic perfectly.
      const params = new URLSearchParams(formData);

      fetch('/updateSchedule', {
        method: 'POST',
        body: params
      })
      .then(response => {
        if (response.ok) {
          alert("Schedule updated successfully!");
        } else {
          alert("Server error updating schedule.");
        }
      })
      .catch(error => {
        console.error("Network error:", error);
        alert("Failed to reach device.");
      });
    }
  </script>

</body>
</html>)rawliteral";
