import React from "react";
import "./styles.css";

const DataDisplay = ({ data, searchTerm }) => {
  if (!searchTerm) return null;

  let filteredData = [];
  const lowerCaseSearchTerm = searchTerm.toLowerCase();
  data.forEach(({ company, products }) => {
    products.forEach((product) => {
      if (
        company.toLowerCase().includes(lowerCaseSearchTerm) ||
        product.name.toLowerCase().includes(lowerCaseSearchTerm)
      ) {
        filteredData.push({ company, ...product });
      }
    });
  });
  const sortedData = filteredData.sort((a, b) => b.score - a.score);

  return (
    <table className="table">
      <thead>
        <tr>
          <th>Company</th>
          <th>Product</th>
          <th>Score</th>
        </tr>
      </thead>
      <tbody>
        {sortedData.map(({ company, name, score }, index) => (
          <tr key={index}>
            <td>{company}</td>
            <td>{name}</td>
            <td>{score}</td>
          </tr>
        ))}
      </tbody>
    </table>
  );
};

export default DataDisplay;
