<?php
require_once ('utils.php');
require_once('TwitterHashtags.php');
require_once('spyc.php');

class TwitterFactory
{
    private $users = array('cartove');
    private $user_limit = 5;
    private $keywords = array();
    private $keywords_limit = 0;
    private $hashtags = array();
    private $hashtags_limit = 0;
    private $keys= array();
    private $Data = array();
    private $twitter_api;

  function __construct($_users,$_user_limit,$_keywords,$_keywords_limit,$_hashtags,$_hashtags_limit,$settings_file_url)
  {
    /** Perform a GET request  **/
    /** Note: Set the GET field BEFORE calling buildOauth(); **/
    $this->users = $_users;
    $this->user_limit =$_user_limit ;
    $this->keywords = $_keywords;
    $this->keywords_limit = $_keywords_limit;
    $this->hashtags = $_hashtags;
    $this->hashtags_limit = $_hashtags_limit;
    $this->keys = spyc_load_file($settings_file_url);
    $this->twitter_api = new TwitterHashtags($this->keys);
  }





  public function fetch_data(){
    // Twitter API 1.1 doesn't allow multi query in the way we wish for, it doesn't grantee that the result would be from both users/hashtags/keywords thus we need to query each key alone. which is annoying because of the datalimit.

    foreach ($this->hashtags as $key => $value) {
      $hashtags[$key] = '#'. $value;
    }

    if(!empty($this->users)){
      array_push($this->Data,$this->twitter_api->twitter_processor($this->users,'?q=from:',$this->user_limit));
    }
    if(!empty($this->hashtags)){
      array_push($this->Data,$this->twitter_api->twitter_processor($this->hashtags,'?q=',$this->hashtags_limit));
    }
    if(!empty($this->keywords)){
      array_push($this->Data,$this->twitter_api->twitter_processor($this->keywords,'?q=',$this->keywords_limit));
    }
    $this->Data = array_merge((array)$this->Data[0],(array)$this->Data[1],(array)$this->Data[2]);
    usort($this->Data, 'date_compare');
    return $this->Data;
  }

}




?>