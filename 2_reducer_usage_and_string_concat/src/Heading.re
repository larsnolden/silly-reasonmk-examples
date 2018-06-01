/* this is a heading component */

/* this is required to tell Reason that this is a component */
let component = ReasonReact.statelessComponent("Heading");

/* the compiler will be looking for this function in each component file */
let make = (~value, _children) => {
  ...component,
  render: self =>
    <div>
      (ReasonReact.string(value))
    </div>,
};
