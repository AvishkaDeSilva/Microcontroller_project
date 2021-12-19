<?php
include('dbconnection.php');
?>
<!DOCTYPE html>
<html>
<head>
<title>IoT Device Web page</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
<link href="layout/styles/layout.css" rel="stylesheet" type="text/css" media="all">
</head>
<body id="top">
    <?php
                                
                                $sql = mysqli_query($con, "SELECT * FROM data ORDER BY id DESC LIMIT 1");
                                $row = mysqli_fetch_array($sql);
                                if ($row > 0) {
                                    ?>
<div class="bgded overlay" style="background-image:url('images/bg.jpg');">
  <div id="pageintro" class="hoc clear"> 
    <article>
      <h3 class="heading">Environment Monitoring System</h3>
      <p>Last Update - <?php echo $row['date']; ?></p>
     
    </article>
  </div>
</div>
<div class="wrapper row3">
  <main class="hoc container clear"> 
    <section id="introblocks">
      <ul class="nospace  elements elements-four">
        <li class="one_quarter">
          <article>
              <h2 style="font-size: 35px;"><?php echo $row['temp']; ?> °C</h2>
              <i class="fas fa-thermometer-three-quarters"></i>
            
            <h6 class="heading">Temperature</h6>
            <p>The degree of hotness or coldness of an environment.</p>
          </article>
        </li>
        <li class="one_quarter">
          <article>
              <h2 style="font-size: 35px;text-transform: lowercase"><?php echo $row['humidity']; ?> %</h2>
              <i class="fas fa-eye-dropper"></i>
           
            <h6 class="heading">Humidity</h6>
            <p>The presence of water vapor in the atmosphere.</p>
          </article>
        </li>
        <li class="one_quarter">
          <article>
              <h2 style="font-size: 35px;text-transform: lowercase"><?php echo $row['pressure']; ?> psi</h2>
              <i class="fas fa-cloud"></i>
            <h6 class="heading">Air Pressure</h6>
            <p>The force exerted on a surface by the air above it as gravity pulls it to Earth.</p>
          </article>
        </li>
        <li class="one_quarter">
          <article>
              <h2 style="font-size: 35px;text-transform: lowercase"><?php echo $row['light']; ?> %</h2>
              <i class="fas fa-umbrella"></i>
            <h6 class="heading">Ambient Light Level</h6>
            <p>The current light level or illuminance is a value.</p>
          </article>
        </li>
      </ul>
    </section>
  </main>
    
</div>
                                <?php } ?>

<div class="wrapper row3">
  <section class="hoc container clear"> 
    <div class="sectiontitle">
      <h6 class="heading font-x2">Past Data</h6>
    </div>
    <canvas id="myChart"></canvas>
  </section>
</div>


<a id="backtotop" href="#top"><i class="fas fa-chevron-up"></i></a>
<script src="layout/scripts/jquery.min.js"></script>
<script src="layout/scripts/jquery.backtotop.js"></script>
<script src="layout/scripts/jquery.mobilemenu.js"></script>
<script src="layout/scripts/jquery.easypiechart.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js"></script>
<script>
<?php 
$xname = "";
$xtitle = "";
$syt1 = "";
$syt2 = "";
$syt3 = "";
$syt4 = "";

    $sqls = mysqli_query($con, "SELECT * from data ORDER BY id DESC LIMIT 20");
    $coo = 0;
    $mnmn=0;
    while ($rows = mysqli_fetch_array($sqls)) {
        $dateadd = strtotime($rows['date']);
        $datess = date("H:i", $dateadd);
        $xname = "'" . $datess . "'," . $xname;
        $syt1 = $rows['temp'] . ',' . $syt1;
        $syt2 = $rows['humidity'] . ',' . $syt2;
        $syt3 = $rows['pressure'] . ',' . $syt3;
        $syt4 = $rows['light'] . ',' . $syt4;
    }

?>
    var xValues = [<?php echo $xname; ?>];

                new Chart("myChart", {
                    type: "line",
                    data: {
                        labels: xValues,
                        datasets: [{
                                label: 'Temperature',
                                data: [<?php echo $syt1; ?>],
                                borderColor: "red",
                                fill: false
                            }, {
                                label: 'Humidity',
                                data: [<?php echo $syt2; ?>],
                                borderColor: "black",
                                fill: false
                            }, {
                                label: 'Air Pressure',
                                data: [<?php echo $syt3; ?>],
                                borderColor: "green",
                                fill: false
                            }, {
                                label: 'Ambient Light Level',
                                data: [<?php echo $syt4; ?>],
                                borderColor: "blue",
                                fill: false
                            }]
                    },
                    options: {
                        resposive: true,
                        legend: {position: 'bottom'},
                        
                    }
                });
                
    </script> 
</body>
</html>