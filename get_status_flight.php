<?php
	echo "hdgshgd";
                $id = '5686558';
                $id = '57cccb2';
                $url = 'http://krk.fr24.com/_external/planedata_json.1.3.php?f=' . $id;
        $json = file_get_contents($url);
        $data = json_decode($json,true);
        $status = $data['status'];
        echo $status;
        if ($status == 'landed') echo "1";
        if ($status == 'airborne') echo "2";

        //print_r(array("lat" => $data['trail'][0], 'lng' => $data['trail'][1]));
        //echo "1";
 ?>
