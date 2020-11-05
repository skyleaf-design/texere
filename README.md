# Texere

## Building the UI

###### install Qt to your system

###### generate the build system

```
cmake -H./ -B./build
```

###### run the build command

```
cd build && make
```

###### run the UI app

```
./texere_ui_x
````


## Building the API

###### create the Python 3 virtualenv

```
python -m venv ./py_env
```


###### activate the virtual env

```
source ./py_env/bin/activate
```


###### install the Python deps

```
pip install uvicorn fastapi
```

###### run the server

```
cd src/server_x/
uvicorn main:app --reload
```

