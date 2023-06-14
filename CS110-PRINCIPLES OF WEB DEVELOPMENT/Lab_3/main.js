/*
    API call to get 10 random tweets and removes duplicates and unneccessary info
    Will add a new tweet if the tweet doesn't exist in the set
*/
var tweets = new Set();
async function sortedTweets() {
    const url = "http://50.21.190.71/get_tweets";
    await fetch(url).then(res => res.json()) .then(data => {  
        // CHAT GPT CODE
        var temp = data.map(tweet => ({
            profilePic: tweet.avatar,
            userName: tweet.user_name,
            date: tweet.date,
            text: tweet.createTextNode
        }));
        temp.sort((a, b) => b.date - a.date);
        for (var i = 0; i < temp.length; i++) {
            if (!tweets.has(temp[i])){
                tweets.add(temp[i]);
                addTweets(temp[i]);
            }
        }
        // END CHAT GPT CODE
    })
    .catch(err => {
        console.log(err); 
        return;
    }); 
    // console.log(Array.from(sortedTweets).sort((a,b) => new Date(b.date) - new Date(a.date)));
    // alert(newTweets.length);
    // console.log(tweets);
    return;
}
/*
sortedTweets().then(() => {
    console.log(tweets);
});
*/

/*
    Adds a new tweet as a div
*/
function addTweets(tweetToAdd) {
    //console.log("adding");
    var newPic = tweetToAdd.profilePic;
    var newName = tweetToAdd.userName;
    var newDate = moment(tweetToAdd.date).format("MM/DD/YYYY");
    var newText = tweetToAdd.text;
    var tweet = document.createElement("div");
    tweet.className = "tweet";

    var profile = document.createElement("img");
    profile.className = "tweetPic";
    profile.src = newPic;

    profile.onerror = function() {
        //alert("Error loading image");
        this.src = "./images/ratatouille.jpg";
        //alert(profile.src);
    };
    var name = document.createElement("a");
    name.className = "tweetName";
    name.appendChild(document.createTextNode(newName));
        
    var date = document.createElement("a");
    date.className = "tweetDate";
    date.appendChild(document.createTextNode(newDate));
        
    var text = document.createElement("a");
    text.className = "tweetContent";
    text.appendChild(document.createTextNode(newText));
        
    tweet.append(profile,name,date,text);
    $(".tweets").append(tweet);
};

/*
    When document is loaded, and the enable checkbox is toggled then 
    begin adding tweets to the feed
*/
document.addEventListener("DOMContentLoaded", async function() {
    var timer; 
    document.getElementById("toggle").addEventListener("change", async function() {
        if (this.checked == true) {
            //alert("on");
            timer = setInterval(await sortedTweets, 5000);
        }
        else {
            //alert("off");
            clearInterval(timer);
        }
    });
});

/*
    Checks for tweets with user text input. 
    Display only the tweets with user input.
    If user input is empty, display all tweets
*/
function search() {
    let input = document.getElementById('input').value
    input=input.toLowerCase();
    // alert(input);
    let x = document.getElementsByClassName('tweet');
      
    for (i = 0; i < x.length; i++) { 
        if (!x[i].innerHTML.toLowerCase().includes(input)) {
            x[i].style.display="none";
        }
        else {
            x[i].style.display="list-item";                 
        }
    }
}