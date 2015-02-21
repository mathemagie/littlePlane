<?php
        require_once './db.php';

        $team_id = $_GET['team_id'];
        $debug = $_GET['debug'];

        if ($team_id == '') exit();
        $flight_id = get_flight_id ( $team_id );
      
        $url = 'http://krk.fr24.com/_external/planedata_json.1.3.php?f=' . $flight_id;
        if ($debug) echo $url . "<br/><br/>";
        $json = file_get_contents($url);
        $data = json_decode($json,true);
        if ($debug) print_r($data);
        $lat = $data['trail'][0];
        $lng = $data['trail'][1];

        $url = 'https://maps.googleapis.com/maps/api/geocode/json?latlng=45.9199,-3.9273';
        $url = 'https://maps.googleapis.com/maps/api/geocode/json?latlng=' . $lat . "," . $lng;

         if ($debug) echo "<hr/>" . $url . "<hr/>";

//        if ($debug) echo "<a href='https://www.google.fr/maps/@" . $lat . "," . $lng . ",6z'>link to google map</a>";

        $json = file_get_contents($url);
        $data_from_google = json_decode($json,true);
        if ($debug) echo "<hr/>";
        if ($debug) print_r($data_from_google);
        $point_water = 0;
        if ($data_from_google['status'] == 'ZERO_RESULTS') $point_water = 1;


        if ($debug) print_r(array("lat" => $data['trail'][0], 'lng' => $data['trail'][1]));
        if ($debug) "<br/><br/><br/>";
        //if ($debug) "<br/><br/><br/>" . print_r($data) . "<br/>";

        $status = $data['status'];
        if ($debug) echo "<br/><br/><b>" . $status . "</b><br/>";
        if ($debug) echo "<br/>sur l\'eau ? <b>" . $point_water . "</b><br/>";
        $status_flight = 0;
        if ($status == 'landed') $status_flight = 1;
        if ($status == 'airborne')  $status_flight = 2;
        if ($status == 'scheduled')  $status_flight = 3;
        //$status_flight = 0;

        echo $status_flight . "|" . $point_water;
?>
