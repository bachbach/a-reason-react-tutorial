let str = ReasonReact.string;

type state = {items: list(TodoType.item)};

type action =
  | AddItem
  | ToggleItem(int)
  | RemoveItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = (): TodoType.item => {
  lastId := lastId^ + 1;
  {id: lastId^, title: "Click a button", completed: true};
};

let make = (_children) => {
  ...component,
  initialState: () => {
    items: [{
      id: 0,
      title: "Write some things to do",
      completed: false
    }]
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem =>
      ReasonReact.Update({items: [newItem(), ...items]})
    | ToggleItem(id) => 
      let items = List.map(
        (item: TodoType.item) => item.id === id ? {...item, completed: !item.completed} : item,
        items
      );

      ReasonReact.Update({items: items}) 
    | RemoveItem(id) => 
      let items = List.filter((item: TodoType.item) => item.id !== id, items);
      ReasonReact.Update({items: items})
    },
  render: ({state: {items}, send}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (str("What to do"))
        <button onClick=((_evt) => send(AddItem))>
          (str("Add something"))
        </button>
      </div>
      <div className="items">
        (
          ReasonReact.array(Array.of_list(
              List.map((item: TodoType.item) => 
                <TodoItem
                  item
                  key=(string_of_int(item.id))
                  onToggle=(() => send(ToggleItem(item.id)))
                  onRemove=(() => send(RemoveItem(item.id)))
                />
              , items)
          ))
        )
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};