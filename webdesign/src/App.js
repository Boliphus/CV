import React, { useState } from "react";
import SearchBox from "./SearchBox";
import DataDisplay from "./DataDisplay";
import "./styles.css";

const data = [
  {
    company: "Apple",
    products: [
      { name: "Phone", score: 4.5 },
      { name: "Laptop", score: 4.8 },
      { name: "Camera", score: 3.9 },
      { name: "Watch", score: 4.3 },
    ],
  },
  {
    company: "Google",
    products: [
      { name: "Phone", score: 4.0 },
      { name: "Laptop", score: 3.9 },
      { name: "Camera", score: 4.1 },
      { name: "Watch", score: 3.7 },
    ],
  },
  {
    company: "Google",
    products: [
      { name: "Phone", score: 4.0 },
      { name: "Laptop", score: 3.9 },
      { name: "Camera", score: 4.0 },
      { name: "Watch", score: 3.7 },
    ],
  },
];

const App = () => {
  const [searchTerm, setSearchTerm] = useState("");

  return (
    <div className="App">
      <SearchBox setSearchTerm={setSearchTerm} />
      <DataDisplay searchTerm={searchTerm} data={data} />
    </div>
  );
};

export default App;