var queryForm;
var lookupButton;

var leftDiv;
var rightDiv;

var mainContentDiv;
var formDiv;
var loadingDiv;
var resultDiv;

var infoDiv;

var loadingText;

var newLookupButton;

var test;

var lookupSuccess = function (data) {
    loadingText.fadeOut(100, function() {
        if (resultDiv.attr('display') == 'none') {
            loadingText.text('Parsing results locally');
            loadingText.fadeIn(100);
        }
    });

    test =data;

    resultDiv.html('No songs found on Touch Tunes');

    if (data['response']['result']['songs'].length > 0) {
        topHitId = data['response']['result']['songs'][0]['id'];

        resultDiv.html('<h3>Top hit song <i>' + data['response']['result']['songs'][0]['title'] + '</i></h3><br><br>');

        $.get( "http://dev.touchtunes.com/music/recommendations/" + topHitId + '?api_key=dm6qzugqhamgy2rzwmw3d9j4', function( data ) {

            recommendSongList = data['response']['songs'];



            if (recommendSongList.length > 0) {
                resultDiv.html(resultDiv.html() + recommendSongList.length + ' recommendations found.<br>');

                recommendSongList.forEach(function(entry) {
                    resultDiv.html(resultDiv.html() + '<div class="recSongDiv well well-sm">' + entry['title'] + '<br><small><i>' + entry['artist']['name']  + '</i></small></div>');
                });
            } else {
                resultDiv.html(resultDiv.html() + 'No TouchTunes recommendations found.<br>');
            }


        });
    }

    //array of filing results returned by parseData() located in filing.js
    //var filings = parseData(JSON.parse(data));

    loadingDiv.fadeOut(100);
    resultDiv.fadeIn(100);

    leftDiv.attr('class', 'col-md-0');
    rightDiv.attr('class', 'col-md-0');
    mainContentDiv.attr('class', 'col-md-12');
};

var lookupError = function (data) {
    loadingText.fadeOut(100, function() {
        if (resultDiv.attr('display') == 'none') {
            loadingText.text('Error encountered');
            loadingText.fadeIn(100);
        }
    });

    loadingDiv.css('display', 'none');
    resultDiv.css('display', 'inline');

    var tmp = '';

    tmp += 'Lookup unsuccessful. System provided error: <br><blockquote cite="https://github.com/ansonl/lobbyist-lookup">' + data.statusText + '</blockquote>';

    resultDiv.html(tmp);

};

var lookupComplete = function (data) {
    loadingDiv.css('display', 'none');
};

$(document).ready(function() {

    $('body').css('display', 'none');
    $('body').fadeIn(100);

    queryForm = $('#queryForm');
    lookupButton = $('#lookupButton');


    leftDiv = $('#leftDiv');
    rightDiv = $('#rightDiv');

    mainContentDiv = $('#mainContentDiv');
    formDiv = $('#formDiv');
    loadingDiv = $('#loadingDiv');
    resultDiv = $('#resultDiv');

    loadingText = $('#loadingText');

    queryForm.submit(function() {

        //    $("#songTitleInput").val($("#songTitleInput").val().replace(" ", "+"));
        //    console.log($("#songTitleInput").val());

            loadingText.text('Looking up filings');
            formDiv.fadeOut(100, function() {
                //Check if ajax callback has already been called
                if (resultDiv.css('display') == 'none')
                    loadingDiv.fadeIn(100);
                });


                var url = 'http://dev.touchtunes.com/music/search';
                $.ajax({
                    type: 'GET',
                    url: url,
                    data: queryForm.serialize(),
                    success: lookupSuccess,
                    error: lookupError,
                    complete: lookupComplete
                });

            return false;
    });
});
