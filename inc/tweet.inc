<?php
require_once('TwitterFactory.inc');
$users = array("cartove");
$user_limit = 5;
$keywords = array("gaza");
$keywords_limit = 1;
$hashtags = array("gaza");
$hashtags_limit = 1;
$settings_file_url = 'inc/settings/keys.yaml';
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
        <span class="_timestamp"><?= $element['Date']?></span>
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
    
    </div>
  </div>
</li>
<?php endforeach; ?>