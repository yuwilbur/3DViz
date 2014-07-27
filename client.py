import httplib2
from flask import Flask
import json

app = Flask(__name__)

@app.route('/images/<artist>')
def artist_image(artist):

	h = httplib2.Http()

	artist = artist.replace(' ', '+')

	request = "http://api.openaura.com/v1/search/artists?q=" + str(artist) + "?q=taylor&api_key=outside-hacks"

	response, content = h.request(request, "GET")
	data = json.loads(content)

	artists = []

	for artist in data:
		artists.append(artist)

	print artists

	if len(artists) > 0:
		#request = "http://api.openaura.com/v1/classic/artists/" + artists[0]['oa_artist_id'] + "?id_type=oa%3Aartist_id&api_key=outside-hacks"
		request = "http://api.openaura.com/v1/stream/artists/" + str(artists[0]['oa_artist_id']) + "?limit=10&id_type=oa:artist_id&api_key=zlA809tV1FCxCb55n5ei0mSmbtHgvpJe"

		response, content = h.request(request, "GET")
		data = json.loads(content)

		particles = data['particles']

		imageUrls = []

		for particle in particles:
			media = particle['media']
			if len(media) > 0:
				imageUrls.append(media[len(media) - 1])

		return json.dumps(imageUrls)
	else:
		return 'no artists found on openaura'

@app.route('/events/<artist>')
def artist_event(artist):

	artist = artist.replace(' ', '+')

	h = httplib2.Http()

	request = "http://api.jambase.com/artists?name=" + str(artist) + "&page=0&api_key=c39y82cv6zuzqatrvadjxdm3"
	response, content = h.request(request, "GET")
	data = json.loads(content)

	print request
	print content

	jamBaseArtists = data['Artists']



	#if len(jamBaseArtists) > 0:
	firstId = jamBaseArtists[0]['Id']

	eventReq = 'http://api.jambase.com/events?artistId=' + str(firstId) + "&page=0&api_key=c39y82cv6zuzqatrvadjxdm3"
	response, content = h.request(eventReq, "GET")
	data = json.loads(content)

	print eventReq

	events = []

	for event in data['Events']:
		events.append(event)

	return json.dumps(events)
	#else:
		#return "No artists found on jambase"

if __name__ == "__main__":
	app.run()
