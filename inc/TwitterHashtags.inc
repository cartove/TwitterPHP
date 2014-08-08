<?php
/**
*  Twitter Hashtag search class 
*  @author Muhammad Negm <alam.hor[at]gmail.com>
 * @license  WTFPL
*/ 
require_once("TwitterAPIExchange.inc");

class TwitterHashtags
{
  private $tweets_url = "https://api.twitter.com/1.1/search/tweets.json";
  private $users_url = "https://api.twitter.com/1.1/statuses/user_timeline.json";
  private $twitter;
  function __construct($keys)
  {
    $this->twitter = new TwitterAPIExchange($keys);
  }

  public function twitter_processor($list,$qtype,$limit,$type)
  {
    static $tweetsCounter = 1;
    $output_array= array();
    if ($type == "User") {
      $url = $this->users_url;  
    }else{
      $url = $this->tweets_url;  
    }
    foreach($list as $key){
      $getfield = $qtype . $key . "&count=" . $limit . "&result_type=recent";

      $api_response= $this->twitter->setGetfield($getfield)
                 ->buildOauth($url, "GET")
                 ->performRequest();
      $response = json_decode($api_response);
      if(array_key_exists("statuses",$response)){
        $statuses = $response->statuses;
      }
      else{
        $statuses = $response;
      }
      foreach($statuses as $tweet)
      {
        if($tweet->retweeted_status != NULL)
          $tweet = $tweet->retweeted_status;
        $text = trim(preg_replace("/\s+/", " ", $tweet->text));
        $text = preg_replace('/((www|http:\/\/)[^ ]+)/', '<a href="\1">\1</a>', $text);
        $text = preg_replace('/#(\\w+)/','<a href="https://twitter.com/hashtag/\1">#\1</a>',$text);
        $text = preg_replace('/@(\\w+)/','<a href="http://twitter.com/\1">@\1</a>',$text);
        array_push($output_array, array("ID" => $tweetsCounter++,
                                        "Text" => $text,
                                        "AuthorName"  => $tweet->user->name,
                                        "UserPicture" => $tweet->user->profile_image_url,
                                        "AuthorTwitterName" =>  $tweet->user->screen_name,
                                        "URL" => "http://twitter.com/{$tweet->user->screen_name}/status/{$tweet->id_str}",
                                        "Media" => $tweet->entities->media[0]->media_url,
                                        "Date" => "$tweet->created_at"));
      }
    }  
            return $output_array;
  }
}


/* tools*/
function date_compare($a, $b)
{
    $t1 = strtotime($a['Date']);
    $t2 = strtotime($b['Date']);
    return $t1 < $t2;
}    