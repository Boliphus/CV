import React, { useState } from "react";
import "./styles.css";
const SearchBox = ({ setSearchTerm }) => {
  const [searchTerm, setSearchTermState] = useState("");

  const handleChange = (event) => {
    setSearchTermState(event.target.value);
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    setSearchTerm(searchTerm);
  };

  return (
    <form onSubmit={handleSubmit} className="search-form">
      <input
        type="text"
        value={searchTerm}
        onChange={handleChange}
        className="search-input"
        placeholder="Search"
      />
      <button type="submit" className="search-button">
        <i className="fa fa-search" />Search
      </button>
    </form>
  );
};

export default SearchBox;