import React,{useEffect, useState} from 'react';
import { MapContainer, TileLayer, Popup,Marker } from 'react-leaflet';
import './map.css';
//import Map from './map.js'

function Geolocation() {

  /*function success(position) {
    
    const latitude  = 22.3193039;//position.coords.latitude;
    const longitude = 114.1693611;//position.coords.longitude;
    const string = latitude;
    console.log(latitude,longitude);

    return <div>
            <div>{string}</div>
            <Map lat={latitude} lng={longitude}/>

          </div>
      
  }


  navigator.geolocation.watchPosition(success);*/
  
  function Map(lat,lng){
    console.log(lat,lng)
    return <div>
        <MapContainer center={[lat, lng]} zoom={20} scrollWheelZoom={false}>
        <TileLayer
          attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
          url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
        />
        <Marker position={[lat, lng]}>
        <Popup>
          A pretty CSS3 popup. <br /> Easily customizable.
        </Popup>
        </Marker>
        </MapContainer>  </div>  
  }; 

  const watchID = navigator.geolocation.watchPosition((position) => {
    Map(position.coords.latitude, position.coords.longitude);
  });

}
/*
function Geolocation(props) {
  const [lat,setLat]=useState(0.0)
  const [lng,setLng]=useState(0.0)
  useEffect(()=>{
    navigator.geolocation.watchPosition((place)=>{
      
      setLat({
        lat: place.coords.latitude,
      })
      setLng({
        lng: place.coords.latitude,
      })

    });

  })
    
  console.log(lat)
  console.log(lng)

    
  return <Map currentlatitude={lat} currentlongitude={lng}/> 
  
    
} */

/*
function Geolocation(props) {
  const [lat,setLat]=useState(0.0)
  const [lng,setLng]=useState(0.0)
  useEffect(()=>{
    navigator.geolocation.watchPosition((place)=>{
      
      setLat({
        lat: place.coords.latitude,
      })
      setLng({
        lng: place.coords.latitude,
      })

    });

  })
    
  console.log(lat)
  console.log(lng)

    
  return <Map currentlatitude={lat} currentlongitude={lng}/> 
  
    
} */

export default Geolocation;
