<div class="stream-container">
  <div class="content-header">
    <div class="header-inner">
      <h2>Tweets</h2>
    </div>
  </div>
  <div class="stream">
    <ol class="stream-items" id="tw-list">
    <?php // include_once ('tweets_cached.php'); // Databse cache?>
    <?php include_once ('tweets.php'); ?>
    <script type="text/javascript">
      function gettweets () {
                      $.ajax({
                  type: "POST",
                  url: "inc/tweets.php",
                  dataType:'text',
                  success: function(response){
                      document.getElementById('tw-list').innerHTML = response + document.getElementById('tw-list').innerHTML;
                  }
      })};
            setInterval(gettweets(), 10000);
    </script>
    </ol>
  </div>
  <div class="twitter-footer">
    <div class="twitter-icon-inner">
        <img class="twitter-icon" src="assets/twitter.png" alt="image" >
    </div>
  </div>
</div>
