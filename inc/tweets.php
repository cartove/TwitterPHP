<?php
require_once('TwitterFactory.php');
require_once ('utils.php');

$users = array();
$user_limit = 0;
$keywords = array("gaza");
$keywords_limit = 4;
$hashtags = array("gaza");
$hashtags_limit = 4;
$settings_file_url = 'settings/keys.yaml';
$Data = new TwitterFactory($users,$user_limit,$keywords,$keywords_limit,$hashtags,$hashtags_limit,$settings_file_url);
$Data = $Data->fetch_data();
?>

<?php
foreach ($Data as $element):
?>
<li class="stream-item">
  <div class="tweet">
    <div class="content">
      <div class="stream-item-header">
        <a class="account-group" href="http://twitter.com/<?=$element['AuthorTwitterName']?>">
        <img class="avatar" src= "<?= $element['UserPicture'] ?>" alt="">
        <strong class="fullname">
          <?= $element['AuthorName'] ?>
        </strong>
        <span class="username">
        <s>@</s><b> <?= $element['AuthorTwitterName'] ?></b>
        </span>
        </a>
        <small class="time">
        <a href="<?= $element['URL']?>" class="tweet-timestamp">
        <span class="_timestamp"><?= time_elapsed_string($element['Date'])?></span>
        </a>
        </small>
      </div>
      <p class="tweet-text">
        <?= $element['Text']; ?>
      </p> 
      <?php if($element['Media']) : ?>    
      <div class="cards-media-container">
        <a class="media" href="<?= $element['URL']?>/photo/1">
          <img src="<?= $element['Media'] ?>" width="100%" alt="image" >
        </a>
      </div>
    <?php endif; ?>
          <div class="intents">
            <a href="<?= $element['Replay']?>" target="_blank" class="icon reply" title="Reply" onclick="window.open(this.href, 'mywin','left=20,top=20,width=600,height=300,toolbar=1,resizable=0'); return false;">Reply</a>
           
            <a href="<?= $element['Retweet']?>"  target="_blank" class="icon retweet" title="Retweet" onclick="window.open(this.href, 'mywin','left=20,top=20,width=600,height=300,toolbar=1,resizable=0'); return false;">Retweet</a>
           
            <a href="<?= $element['Favorite']?>" target="_blank" class="icon favorite" rel="favorite" title="Favorite" onclick="window.open(this.href, 'mywin','left=20,top=20,width=600,height=300,toolbar=1,resizable=0'); return false;">Favorite</a> 

            <a href="<?= $element['URL']?>" target="_blank" class="icon permalink" rel="permalink" title="View on Twitter"> View on Twitter </a> 
        </div>
    </div>
  </div>
</li>
<?php endforeach; ?>