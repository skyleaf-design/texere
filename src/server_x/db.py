import os

from fastapi import FastAPI
from tortoise.contrib.fastapi import register_tortoise


def init_db(app: FastAPI) -> None:
    register_tortoise(
        app,
        db_url=os.environ.get("DATABASE_URL"),
        modules={"models": ["models"]},
        generate_schemas=False,
        add_exception_handlers=True,
    )
