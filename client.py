import httplib2
import json

h = httplib2.Http()

response, content = h.request("http://localhost:5000/", "GET")

print 'Hello World GET Request:'
print '\tresponse', response
print '\tcontent', content

response, content = h.request("http://localhost:5000/images/Boards_of_Canada", "GET")
data = json.loads(content)

print '\nExample Artist Image GET Request:'
print '\tresponse', response
print '\tcontent', content
print '\tArtist Name Returned', data['artist']
