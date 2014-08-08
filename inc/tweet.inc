<?php
require_once('spyc.inc');
require_once('TwitterHashtags.inc');

/** Perform a GET request  **/
/** Note: Set the GET field BEFORE calling buildOauth(); **/
$users = array("cartove");
$user_limit = 3;
$keywords = array();
$keywords_limit = 0;
$hashtags = array();
$hashtags_limit = 0;



$keys = Spyc::YAMLLoad('inc/settings/keys.yaml');      // Reading the keys settings please add your own keys


// Twitter API 1.1 doesn't allow multi query in the way we wish for, it doesn't grantee that the result would be from both users/hashtags/keywords thus we need to query each key alone. which is annoying because of the datalimit.

$Data = array();
$twitter_api = new TwitterHashtags($keys);


foreach ($hashtags as $key => $value) {
  $hashtags[$key] = '#'. $value;
}

if(!empty($users)){
  array_push($Data,$twitter_api->twitter_processor($users,'?screen_name=',$user_limit,'User'));
}
if(!empty($hashtags)){
  array_push($Data,$twitter_api->twitter_processor($hashtags,'?q=',$hashtags_limit,'Hashtag'));
}
if(!empty($keywords)){
  array_push($Data,$twitter_api->twitter_processor($keywords,'?q=',$keywords_limit,'Keyword'));
}
$Data = array_merge((array)$Data[0],(array)$Data[1],(array)$Data[2]);
usort($Data, 'date_compare');
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