
type action =
  | ChangeResult(string)
  | RequestData;

type state = {
  result: string,
}

let networkRequest = 
  Js.Promise.(
    Fetch.fetch("https://raw.githubusercontent.com/reach/router/master/.gitignorehttps://raw.githubusercontent.com/facebook/react/master/packages/react/index.js")
    |> then_(Fetch.Response.text)
  )

let component = ReasonReact.reducerComponent("Page");

let make = (_children) => {
  ...component,
  initialState: () => {
    result: ""
  },
  reducer: (action, state) =>
    switch(action) {
    | ChangeResult(result) => ReasonReact.Update({
      ...state,
      result,
    })
    | RequestData => ReasonReact.SideEffects(self =>
      networkRequest
      |> Js.Promise.then_(value => {
        Js.log(value);
        self.send(ChangeResult(value));
        Js.Promise.resolve();
      })
      |> ignore
      )
    },

  render: self => 
    <div>
      <h2>(ReasonReact.string("Static Fetch request"))</h2>
      <button onClick={_event => self.send(RequestData)}>(ReasonReact.string("Fetch"))</button>
      <div>(ReasonReact.string(self.state.result))</div>
    </div>
};