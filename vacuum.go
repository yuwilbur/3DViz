package main

import (
	"fmt"
    "io/ioutil"
    "encoding/JSON"
	"net/http"
    "net/url"
	"os"
	"time"
    //"strconv"
)

type OpenAuraArtist struct {
    ArtistId string `json:"oa_artist_id"`
    Name string `json:"name"`
}

type OpenAuraArtistInfo struct {
    ArtistId string `json:"oa_artist_id"`
    Name interface{} `json:"name"`
    CoverPhotoArray []interface{} `json:"cover_photo"`
}

type JamBaseArtist struct {
    ArtistId string `json:"Id"`
    Name string `json:"Name"`
}

type JamBaseArtistSearch struct {
    Info interface{} `json:"Info"`
    Artists []JamBaseArtist `json:"Artists"`
}



//Return artist info listing for an OA artist id
func openAuraArtistInfo(artistId string) string {
    query := fmt.Sprintf("http://api.openaura.com/v1/info/artists/%s?id_type=oa:artist_id&api_key=outside-hacks", artistId)

    res, err := http.Get(query)
    if (err != nil) {
        panic(err)
    }

    robots, err := ioutil.ReadAll(res.Body)
    res.Body.Close()
    if err != nil {
        panic(err)
    }

    return string(robots)
}

//Return array of OAArtists
func openAuraSearchArtist(values url.Values) []OpenAuraArtist {
    if (len(values["artistName"]) > 0) {
        query := fmt.Sprintf("http://api.openaura.com/v1/search/artists?q=%s&limit=10&api_key=outside-hacks", values["artistName"][0])

        res, err := http.Get(query)
        if (err != nil) {
            panic(err)
        }

        robots, err := ioutil.ReadAll(res.Body)
        res.Body.Close()
        if err != nil {
            panic(err)
        }

        //fmt.Println(string(robots))

        var list []OpenAuraArtist

        json.Unmarshal(robots, &list)
        //fmt.Println(list[0].ArtistId)
        return list
    } else {
        return nil
    }
}

//Return array of jambase artists
func jamBaseSearchArtist(values url.Values) interface{} {
    if (len(values["artistName"]) > 0) {
        query := fmt.Sprintf("http://api.jambase.com/artists?name=%s&api_key=c39y82cv6zuzqatrvadjxdm3", values["artistName"][0])

        res, err := http.Get(query)
        if (err != nil) {
            panic(err)
        }

        robots, err := ioutil.ReadAll(res.Body)
        res.Body.Close()
        if err != nil {
            panic(err)
        }

        //fmt.Println(string(robots))

        var result JamBaseArtistSearch

        json.Unmarshal(robots, &result)
        fmt.Println(result)

        return result
    } else {
        return nil
    }
}


func Extend(slice []interface{}, element interface{}) []interface{} {
    n := len(slice)
    if n == cap(slice) {
        // Slice is full; must grow.
        // We double its size and add 1, so if the size is zero we still grow.
        newSlice := make([]interface{}, len(slice), 2*len(slice)+1)
        copy(newSlice, slice)
        slice = newSlice
    }
    slice = slice[0 : n+1]
    slice[n] = element
    return slice
}

//handle all api requests
func apiHandler(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	//fmt.Println(r.Form)

	//bypass same origin policy
	w.Header().Set("Access-Control-Allow-Origin", "*")


	apiService := r.Form["service"]
    workType := r.Form["workType"]
	//songTitle := r.Form["song"]


    if (len(apiService) > 0) {
        switch apiService[0] {
            case "openaura":
                //fmt.Println("Search for ", r.Form["artistName"])
                obj := openAuraSearchArtist(r.Form)
                if (len(workType) > 0 && workType[0] == "0") { //return first artist result info
                    //fmt.Println(openAuraArtistInfo(obj[0].ArtistId))
                    var coverPhoto OpenAuraArtistInfo
                        json.Unmarshal([]byte(openAuraArtistInfo(obj[0].ArtistId)), &coverPhoto)
                    fmt.Println(coverPhoto)
                    fmt.Println(coverPhoto.Name)
                } else { //return artist list
                    b, err := json.Marshal(obj)
                    if (err != nil) {
                        panic(err)
                    }

                    fmt.Fprintf(w, string(b))
                }

            case "jambase":
                fmt.Println("Search for ", r.Form["artistName"])
                obj := jamBaseSearchArtist(r.Form)
                /*
                if (len(workType) > 0) { //return first artist result info
                    fmt.Fprintf(w, openAuraArtistInfo(obj[0].ArtistId))
                } else { //return artist list
                    b, err := json.Marshal(obj)
                    if (err != nil) {
                        panic(err)
                    }

                    fmt.Fprintf(w, string(b))
                }
                */
                b, err := json.Marshal(obj)
                if (err != nil) {
                    panic(err)
                }

                fmt.Fprintf(w, string(b))
            default:
                //link := "error"
        }
    }

    //fmt.Println(link)

    /*
    link := "http://api.openaura.com/v1/search/artists?q=taylor&api_key=outside-hacks"

    fmt.Println("Sending GET request to " + link + "...");

    res, err := http.Get(link)

    if (err != nil) {
        panic(err)
    }

    robots, err := ioutil.ReadAll(res.Body)
	res.Body.Close()
	if err != nil {
		panic(err)
	}

    fmt.Println(string(robots))
    */

}

func server() {
	http.HandleFunc("/api/", apiHandler)
	//http.HandleFunc("/", handler)

    err := http.ListenAndServe(":"+os.Getenv("PORT"), nil)
    if err != nil {
      panic(err)
    }

    fmt.Println("listening on port " + os.Getenv("PORT"))
}

func main() {
    go server()


    ticker := time.NewTicker(60 * 60 * 24 * time.Second)
    for {
        select {
            case <- ticker.C:
        }
    }

	fmt.Println("server end")
}
