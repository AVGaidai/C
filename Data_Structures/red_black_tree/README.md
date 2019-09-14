# RED-BLACK TREE

Structure red-black tree:

<table>
  <tr>
    <th> Field </th>
    <th> Description </th>
  </tr>
  <tr>
    <td> root </td>
    <td> pointer to root of the tree </td>
  </tr>
  <tr>
    <td> nil </td>
    <td> pointer to nil element </td>
  </tr>
  <tr>
    <td> nmemb </td>
    <td> number of members in the tree </td>
  </tr>
</table>

Structure node of red-black tree:

<table>
  <tr>
    <th> Field </th>
    <th> Description </th>
  </tr>
  <tr>
    <td> parent </td>
    <td> pointer to parent of the node </td>
  </tr>
  <tr>
    <td> left </td>
    <td> pointer to left child of the node </td>
  </tr>
  <tr>
    <td> right </td>
    <td> pointer to right child of the node </td>
  </tr>
  <tr>
    <td> </td>
    <td> </td>
  </tr>
  <tr>
    <td> color </td>
    <td> color of the node </td>
  </tr>
  <tr>
    <td> key </td>
    <td> key of the node </td>
  </tr>
  <tr>
    <td> size </td>
    <td> size of value </td>
  </tr>
  <tr>
    <td> value </td>
    <td> pointer to value </td>
  </tr>
</table>


Available functions:

1) The initializer red-black tree function (RBT_Init(...)). <br>
2) The function of inserting an node with the specified key and value (RBT_Insert(...)). <br>
3) The find function by key (RBT_Find(...)). <br>
4) The function of deleting node with specified key (RBT_Delete(...)). <br>
5) The print red-black tree function (RBT_Print(...)). <br>
6) The delete red-black tree function (RBT_Free(...)). <br>

