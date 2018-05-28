type state = {
  val1: string,
  val2: string,
  result: string,
};

type action = 
  | ChangeValue1(string)
  | ChangeValue2(string)
  | Combine
  | Clear;

let component = ReasonReact.reducerComponent("Add");

let make = (_children) => {
  ...component,
  initialState: () => {
    val1: "",
    val2: "",
    result: ""
  },

  reducer: (action, state) =>
    switch (action) {
    | ChangeValue1(value) =>
     ReasonReact.Update({
      ...state,
      val1: value
    })
    | ChangeValue2(value) => 
     ReasonReact.Update({
        ...state,
        val2: value
    })
    | Combine => ReasonReact.Update({
      ...state,
      result: state.val1 ++ state.val2
    })
    | Clear => ReasonReact.Update({
      ...state,
      val1: "",
      val2: "",
      result: ""
    })
    },

    render: self =>
      <div>
        (ReasonReact.string("Just concats two strings"))
        <div>
          <input onChange=(event => self.send(ChangeValue1(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value))) value=(self.state.val1) />
          <input onChange=(event => self.send(ChangeValue2(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value))) value=(self.state.val2) />
          <div>
            <button onClick=(_event => self.send(Combine))>(ReasonReact.string("Combine"))</button>
            <button onClick=(_event => self.send(Clear))>(ReasonReact.string("Clear"))</button>
          </div>
          <div>
            {ReasonReact.string(self.state.result)}
          </div>
        </div>
      </div>,
}