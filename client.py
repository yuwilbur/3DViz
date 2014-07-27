import httplib2
from flask import Flask
import json

app = Flask(__name__)

@app.route('/images/<artist>')
def artist_image(artist):

	h = httplib2.Http()

	request = "http://api.openaura.com/v1/search/artists?q=" + artist + "?q=taylor&api_key=outside-hacks"

	response, content = h.request(request, "GET")
	data = json.loads(content)

	print 'Hello World GET Request:'
	print '\tresponse', response
	print '\tcontent', content

	artists = []

	for artist in data:
		artists.append(artist)

	request = "http://api.openaura.com/v1/classic/artists/" + artists[0]['oa_artist_id'] + "?id_type=oa%3Aartist_id&api_key=outside-hacks"

	response, content = h.request(request, "GET")
	data = json.loads(content)

	artistImages = data['artist_images']

	imageUrls = []

	for image in artistImages:
		imageUrls.append(image['url'])

	print imageUrls

	return json.dumps(imageUrls)

if __name__ == "__main__":
	app.run()
