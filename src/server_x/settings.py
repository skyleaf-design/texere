TORTOISE_ORM = {
    "connections": {
        "default": "postgres://texere:texere@localhost:5432/texere"
    },
    "apps": {
        "models": {
            "models": ["models", "aerich.models"],
            "default_connection": "default",
        },
    },
}
