import { MapContainer, TileLayer, Popup,Marker,useMapEvents, useMapEvent} from 'react-leaflet';
import React, { useEffect, useState } from 'react';
//import Leaflet,{} from 'react-leaflet';

import './map.css';

function Map(){

  /*
  const [position,setPos]=useState([25,121.5]);
  useEffect(() => {
    navigator.geolocation.watchPosition((place)=>{
      setPos([place.coords.latitude,place.coords.longitude])
      
    });
  });*/
  
  function LocationMarker() {
    const [position, setPosition] = useState(null)
    const map = useMapEvents({
      zoomstart() {
        map.locate()
      },
      locationfound(e) {
        console.log(e)  
        setPosition(e.latlng)
        map.panTo(e.latlng)
      },
    })
  
    return position === null ? null : (
      <Marker position={position}>
        <Popup>You are here</Popup>
      </Marker>
    )
  }
  //console.log(position)
  return <MapContainer center={{ lat: 25, lng: 121.5 }} zoom={20} scrollWheelZoom={false}>
      <TileLayer
        attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
      />
      <LocationMarker />
      </MapContainer>    
}; 

/*

function Map(){

  function error(){
    alert('error')
  };
  const [position,setPos]=useState([25,121.5]);
  navigator.geolocation.watchPosition((place)=>{
    setPos([place.coords.latitude,place.coords.longitude])
  },error());
  //useMapEvent().panTo(position)
    

  console.log(position)
  return <MapContainer center={position} zoom={20} scrollWheelZoom={false}>
      useMapEvent().panTo(position)
      <TileLayer
        attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
      />
      <Marker position={position}>
      <Popup>
        A pretty CSS3 popup. <br /> Easily customizable.
      </Popup>
      </Marker>
      </MapContainer>    
}; 
*/

export default Map;