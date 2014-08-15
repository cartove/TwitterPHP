<?php
/**
*  Twitter Hashtag search class 
*  @author Muhammad Negm <alam.hor[at]gmail.com>
 * @license  WTFPL
*/ 
require_once("TwitterAPIExchange.inc");

class TwitterHashtags
{
  private $tweets_url = 'https://api.twitter.com/1.1/search/tweets.json';
  private $twitter;
  function __construct($keys)
  {
    $this->twitter = new TwitterAPIExchange($keys);
  }

  public function twitter_processor($list,$qtype,$limit)
  {
    $output_array= array();
    $url = $this->tweets_url;  
    
    foreach($list as $key){
      $getfield = $qtype . $key. "&count=" . $limit . "&result_type=recent";

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
        
        $maybeVideo = $tweet->entities->urls[0]->expanded_url;
        if ($tweet->entities->media == NULL && strpos($maybeVideo,'youtu.be') !== false) {
          $media_thumb = "http://img.youtube.com/vi/". str_replace("http://youtu.be/","",$maybeVideo) ."/maxresdefault.jpg";
        }
        else{
        $media_thumb = $tweet->entities->media[0]->media_url;
        }
        
        $text = trim(preg_replace("/\s+/", " ", $tweet->text));
        $text = preg_replace('/((http:\/\/)[^ ]+)/', '<a href="\1">\1</a>', $text);
        $text = preg_replace('/((https:\/\/)[^ ]+)/', '<a href="\1">\1</a>', $text);
        $text = preg_replace('/#(\\w+)/','<a href="http://twitter.com/hashtag/\1">#\1</a>',$text);
        $text = preg_replace('/@(\\w+)/','<a href="http://twitter.com/\1">@\1</a>',$text);
        array_push($output_array, array("Text" => $text,
                                        "AuthorName"  => $tweet->user->name,
                                        "UserPicture" => $tweet->user->profile_image_url,
                                        "AuthorTwitterName" =>  $tweet->user->screen_name,
                                        "URL" => "http://twitter.com/{$tweet->user->screen_name}/status/{$tweet->id_str}",
                                        "Media" => $media_thumb,
                                        "Date" => "$tweet->created_at"));

      }
    } 
    print_r($output_array);
            return $output_array;
  }
}

