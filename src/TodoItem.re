let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item: TodoType.item, ~onToggle, ~onRemove, children) => {
  {
    ...component,
    render: (self) =>
      <div className="item" onClick=((_evt) => onToggle())>
        <input
          type_="checkbox"
          defaultChecked=(item.completed)
        />
        <span>(str(item.title))</span>
        <span className="item__remove-button" onClick=((_e) => onRemove())>(str("x"))</span>
      </div>
  }
};